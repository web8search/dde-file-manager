/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *               2016 ~ 2018 dragondjf
 *
 * Author:     dragondjf<dingjiangfeng@deepin.com>
 *
 * Maintainer: dragondjf<dingjiangfeng@deepin.com>
 *             zccrs<zhangjide@deepin.com>
 *             Tangtong<tangtong@deepin.com>
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

#ifndef DDIRITERATOR_H
#define DDIRITERATOR_H

#include "dabstractfileinfo.h"

class DDirIterator
{
public:
    enum {
        // 把目录中的文件按文件系统的inode排序, 用于目录复制/移动
        // 在机械硬盘上, 读取排序后的文件内容会减少很多磁盘寻道和磁头定位的时间
        SortINode = 0x800
    };

    virtual ~DDirIterator() {}

    virtual DUrl next() = 0;
    virtual bool hasNext() const = 0;
    virtual void close() {}

    virtual QString fileName() const = 0;
    // Returns the full file url for the current directory entry.
    virtual DUrl fileUrl() const = 0;
    virtual const DAbstractFileInfoPointer fileInfo() const = 0;
    //判读ios手机，传输慢，需要特殊处理优化
    virtual const DAbstractFileInfoPointer optimiseFileInfo() const{return DAbstractFileInfoPointer(nullptr);}
    // Returns the base url of the iterator.
    virtual DUrl url() const = 0;
    //判读ios手机，传输慢，需要特殊处理优化
    inline void setOptimise(const bool boptimise){m_boptimise = boptimise;}

    virtual bool enableIteratorByKeyword(const QString &keyword) {Q_UNUSED(keyword); return false;}
public:
    bool m_boptimise = false;
};

typedef QSharedPointer<DDirIterator> DDirIteratorPointer;

Q_DECLARE_METATYPE(DDirIteratorPointer)
#endif // DDIRITERATOR_H
