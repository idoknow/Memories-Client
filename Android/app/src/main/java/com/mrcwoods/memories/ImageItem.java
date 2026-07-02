package com.mrcwoods.memories;

public class ImageItem {
    public long id;
    public String url;
    public long uploadedAt;

    public ImageItem(long id, String url, long uploadedAt) {
        this.id = id;
        this.url = url;
        this.uploadedAt = uploadedAt;
    }
}