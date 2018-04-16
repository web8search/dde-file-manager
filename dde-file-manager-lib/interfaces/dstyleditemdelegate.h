/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DSTYLEDITEMDELEGATE_H
#define DSTYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QTextOption>

class DFileViewHelper;
class DStyledItemDelegatePrivate;
class DStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DStyledItemDelegate(DFileViewHelper *parent);
    ~DStyledItemDelegate();

    DFileViewHelper *parent() const;

    QModelIndex editingIndex() const;
    QWidget *editingIndexWidget() const;

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QString displayText(const QVariant &value, const QLocale &locale) const Q_DECL_OVERRIDE;

    virtual QModelIndexList hasWidgetIndexs() const;
    virtual void hideAllIIndexWidget();
    virtual void hideNotEditingIndexWidget();
    virtual void commitDataAndCloseActiveEditor();
    virtual QRect fileNameRect(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QList<QRect> paintGeomertys(const QStyleOptionViewItem &option, const QModelIndex &index) const = 0;

    virtual int iconSizeLevel() const;
    virtual int minimumIconSizeLevel() const;
    virtual int maximumIconSizeLevel() const;

    virtual int increaseIcon();
    virtual int decreaseIcon();
    virtual int setIconSizeByIconSizeLevel(int level);

    virtual void updateItemSizeHint() = 0;

    virtual QRect drawText(QPainter *painter, const QString &text, const QRect &boundingRect,
                           int backgroundMargins, qreal radius, const QBrush &background,
                           int lineHeight, QTextOption::WrapMode wordWrap = QTextOption::WrapAtWordBoundaryOrAnywhere,
                           Qt::TextElideMode mode = Qt::ElideMiddle, int flags = Qt::AlignCenter,
                           const QColor &shadowColor = QColor()) const;

protected:
    DStyledItemDelegate(DStyledItemDelegatePrivate &dd, DFileViewHelper *parent);

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QList<QRect> getCornerGeometryList(const QRect &baseRect, const QSize &cornerSize) const;

    static QPixmap getIconPixmap(const QIcon &icon, const QSize &size, qreal pixelRatio, QIcon::Mode mode = QIcon::Normal, QIcon::State state = QIcon::Off);
    static void paintIcon(QPainter *painter, const QIcon &icon, const QRect &rect, Qt::Alignment alignment = Qt::AlignCenter,
                          QIcon::Mode mode = QIcon::Normal, QIcon::State state = QIcon::Off);

    QScopedPointer<DStyledItemDelegatePrivate> d_ptr;

    Q_PRIVATE_SLOT(d_ptr, void _q_onRowsInserted(const QModelIndex &parent, int first, int last))
    Q_PRIVATE_SLOT(d_ptr, void _q_onRowsRemoved(const QModelIndex &parent, int first, int last))

    Q_DECLARE_PRIVATE(DStyledItemDelegate)
    Q_DISABLE_COPY(DStyledItemDelegate)
};

#endif // DSTYLEDITEMDELEGATE_H
