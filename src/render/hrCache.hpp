// openhomm - open source clone of Heroes of Might and Magic III
// Copyright (C) 2009-2010 openhomm developers team (see AUTHORS)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#pragma once
#include "hrGraphicsItem.hpp"

#include "hrFilesystem.hpp"

class hrCacheItem
{
public:
    hrCacheItem() : curBlock(0)
    {
        blocks.append(Block());
    }
    ~hrCacheItem()
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            const Block& b = blocks.at(i);
            for (int j = 0; j < b.frames.size(); j++)
                glDeleteTextures(1, &b.frames.at(j));
        }
    }
    GLuint getFrame(int frame) const
    {
        const Block &b = blocks.at(curBlock);
        Q_ASSERT(frame >= 0 && frame < b.frames.size());
        return b.frames.at(frame);
    }
    void addFrame(GLuint tx)
    {
        blocks[curBlock].frames.append(tx);
    }
    int countFrames() const
    {
        return blocks.at(curBlock).frames.size();
    }
    void setSize(const QSize &s)
    {
        size = s;
    }
    QSize getSize() const
    {
        return size;
    }
private:
    struct Block
    {
        QVector<GLuint> frames;
    };
    QVector<Block> blocks;

    int curBlock;
    QSize size;
};

class hrCache
{
public:
    ~hrCache();

    static hrCache& getInstance()
    {
        static hrCache cache;
        return cache;
    }

    GLuint getTexture(const hrGraphicsItem& item);
    hrGraphicsItem loadItem(const QString& name, bool notDeletable = false);
    void setContext(const QGLContext *context);

    void setFilesystem(hrFilesystem* filesystem)
    {
        _filesystem = filesystem;
    }

    QByteArray getResource(const QString& resName);

private:
    GLuint target;
    GLuint format;

    hrFilesystem* _filesystem;

    QCache<hrCacheKey, hrCacheItem> cache;
    QMap<hrCacheKey, hrCacheItem*> map;

    QMap<hrCacheKey, QString> files;

    //QFile cacheFile;
    //QHash<QString, qint64> fat;

    hrCache();

    hrCacheItem* Load(const QString &name) const;
    GLuint Load(const QImage &im) const;
    //hrCacheItem* LoadPrepared(qint64 pos);
    //hrCacheItem* LoadAndPrepare(const QString &name);

    GLuint bindImage(const GLvoid* image
                     , int width
                     , int height
                     , bool compressed
                     , int size) const;

    int getCompressedImageSize() const;

    QImage ImageToPOT(const QImage &im) const;
    void checkExtensions();
};
