/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"

#ifndef _PreComp_
# include <QApplication>
# include <QPainter>
#endif

#include <Base/Console.h>
#include <App/Application.h>
#include <App/Document.h>
#include "PropertyEditor.h"
#include "PropertyItemDelegate.h"
#include "PropertyModel.h"

using namespace Gui::PropertyEditor;

PropertyEditor::PropertyEditor(QWidget *parent)
    : QTreeView(parent), autoupdate(false), committing(false), delaybuild(false)
{
    propertyModel = new PropertyModel(this);
    setModel(propertyModel);

    PropertyItemDelegate* delegate = new PropertyItemDelegate(this);
    delegate->setItemEditorFactory(new PropertyItemEditorFactory);
    setItemDelegate(delegate);

    setAlternatingRowColors(true);
    setRootIsDecorated(true);
}

PropertyEditor::~PropertyEditor()
{
}

void PropertyEditor::setAutomaticDocumentUpdate(bool v)
{
    autoupdate = v;
}

bool PropertyEditor::isAutomaticDocumentUpdate(bool) const
{
    return autoupdate;
}

QStyleOptionViewItem PropertyEditor::viewOptions() const
{
    QStyleOptionViewItem option = QTreeView::viewOptions();
    option.showDecorationSelected = true;
    return option;
}

void PropertyEditor::closeEditor (QWidget * editor, QAbstractItemDelegate::EndEditHint hint)
{
    if (autoupdate) {
        App::Document* doc = App::GetApplication().getActiveDocument();
        if (doc && doc->isTouched())
            doc->recompute();
    }
    QTreeView::closeEditor(editor, hint);
}

void PropertyEditor::commitData (QWidget * editor)
{
    committing = true;
    QTreeView::commitData(editor);
    committing = false;
    if (delaybuild) {
        delaybuild = false;
        propertyModel->buildUp(PropertyModel::PropertyList());
    }
}

void PropertyEditor::editorDestroyed (QObject * editor)
{
    QTreeView::editorDestroyed(editor);
}

void PropertyEditor::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
    QTreeView::currentChanged(current, previous);
    if (previous.isValid())
        closePersistentEditor(model()->buddy(previous));
    if (current.isValid())
        openPersistentEditor(model()->buddy(current));
}

void PropertyEditor::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QTreeView::drawBranches(painter, rect, index);

    QStyleOptionViewItem opt = viewOptions();
    PropertyItem *property = static_cast<PropertyItem*>(index.internalPointer());
    if (property && property->isSeparator()) {
        painter->fillRect(rect, opt.palette.dark());
    //} else if (selectionModel()->isSelected(index)) {
    //    painter->fillRect(rect, opt.palette.brush(QPalette::Highlight));
    }

    //QPen savedPen = painter->pen();
    //QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    //painter->setPen(QPen(color));
    //painter->drawLine(rect.x(), rect.bottom(), rect.right(), rect.bottom());
    //painter->setPen(savedPen);
}

void PropertyEditor::buildUp(const PropertyModel::PropertyList& props)
{
    if (committing) {
        Base::Console().Warning("While committing the data to the property the selection has changed.\n");
        delaybuild = true;
        return;
    }

    QModelIndex index = this->currentIndex();
    QStringList propertyPath = propertyModel->propertyPathFromIndex(index);
    if (!propertyPath.isEmpty())
        this->selectedProperty = propertyPath;
    propertyModel->buildUp(props);
    if (!this->selectedProperty.isEmpty()) {
        QModelIndex index = propertyModel->propertyIndexFromPath(this->selectedProperty);
        this->setCurrentIndex(index);
    }

    propList = props;
}

void PropertyEditor::updateProperty(const App::Property& prop)
{
    // forward this to the model if the property is changed from outside
    if (!committing)
        propertyModel->updateProperty(prop);
}

void PropertyEditor::appendProperty(const App::Property& prop)
{
    // check if the parent object is selected
    std::string editor = prop.getEditorName();
    if (editor.empty())
        return;
    App::PropertyContainer* parent = prop.getContainer();
    std::string context = prop.getName();

    bool canAddProperty = (!propList.empty());
    for (PropertyModel::PropertyList::iterator it = propList.begin(); it != propList.end(); ++it) {
        if (it->second.empty() || it->second.size() > 1) {
            canAddProperty = false;
            break;
        }
        else if (it->second.front()->getContainer() != parent) {
            canAddProperty = false;
            break;
        }
    }

    if (canAddProperty) {
        std::vector<App::Property*> list;
        list.push_back(const_cast<App::Property*>(&prop));
        std::pair< std::string, std::vector<App::Property*> > pair = std::make_pair(context, list);
        propList.push_back(pair);
        propertyModel->appendProperty(prop);
    }
}

void PropertyEditor::removeProperty(const App::Property& prop)
{
    for (PropertyModel::PropertyList::iterator it = propList.begin(); it != propList.end(); ++it) {
        // find the given property in the list and remove it if it's there
        std::vector<App::Property*>::iterator pos = std::find(it->second.begin(), it->second.end(), &prop);
        if (pos != it->second.end()) {
            it->second.erase(pos);
            // if the last property of this name is removed then also remove the whole group
            if (it->second.empty()) {
                propList.erase(it);
            }
            propertyModel->removeProperty(prop);
            break;
        }
    }
}

#include "moc_PropertyEditor.cpp"