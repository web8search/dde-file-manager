/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Gary Wang <wzc782970009@gmail.com>
 *
 * Maintainer: Gary Wang <wangzichong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "dfmglobal.h"
#include <DListView>

DWIDGET_USE_NAMESPACE

DFM_BEGIN_NAMESPACE
class DFMSideBarItem;
typedef QDropEvent DFMDragEvent;
class DFMSideBarView : public DListView
{
    Q_OBJECT
public:
    DFMSideBarView(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    QModelIndex indexAt(const QPoint &p) const Q_DECL_OVERRIDE;
    QModelIndex getPreviousIndex() const;
    QModelIndex getCurrentIndex() const;
    void currentChanged(const QModelIndex &previous);
    DFMSideBarItem *itemAt(const QPoint &pt);

protected:
    bool onDropData(DUrlList srcUrls, DUrl dstUrl, Qt::DropAction action) const;
    Qt::DropAction canDropMimeData(DFMSideBarItem *item,const QMimeData *data, Qt::DropActions actions) const;
    bool isAccepteDragEvent(DFMDragEvent *event);
signals:
    void requestRemoveItem();

private slots:
    void onRowCountChanged();

private:
    bool fetchDragEventUrlsFromSharedMemory();
    int previousRowCount;
    QPoint dropPos;
    QString dragItemName;
    int dragRow;
    QModelIndex m_previous;
    QModelIndex m_current;

    QList<QUrl> m_urlsForDragEvent;
};

DFM_END_NAMESPACE
