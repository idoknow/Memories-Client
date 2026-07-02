package com.mrcwoods.memories;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.security.MessageDigest;

public class ImageCache {
    public interface BitmapCallback {
        void onReady(Bitmap bitmap);
        void onError(String message);
    }

    private final File directory;

    public ImageCache(Context context) {
        directory = new File(context.getCacheDir(), "images");
        if (!directory.exists()) {
            directory.mkdirs();
        }
    }

    public void load(String url, BitmapCallback callback) {
        new Thread(() -> {
            try {
                File file = fileFor(url);
                if (!file.exists()) {
                    InputStream input = new URL(url).openStream();
                    FileOutputStream output = new FileOutputStream(file);
                    byte[] buffer = new byte[8192];
                    int read;
                    while ((read = input.read(buffer)) != -1) {
                        output.write(buffer, 0, read);
                    }
                    input.close();
                    output.close();
                }
                Bitmap bitmap = BitmapFactory.decodeFile(file.getAbsolutePath());
                if (bitmap == null) {
                    callback.onError("图片解码失败");
                } else {
                    callback.onReady(bitmap);
                }
            } catch (Exception exception) {
                callback.onError(exception.getMessage());
            }
        }).start();
    }

    public long sizeBytes() {
        return sizeOf(directory);
    }

    public void clear() {
        clear(directory);
        directory.mkdirs();
    }

    private File fileFor(String url) throws Exception {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(url.getBytes());
        StringBuilder name = new StringBuilder();
        for (byte value : hash) {
            name.append(String.format("%02x", value));
        }
        return new File(directory, name.toString());
    }

    private long sizeOf(File file) {
        if (file == null || !file.exists()) {
            return 0;
        }
        if (file.isFile()) {
            return file.length();
        }
        long total = 0;
        File[] children = file.listFiles();
        if (children != null) {
            for (File child : children) {
                total += sizeOf(child);
            }
        }
        return total;
    }

    private void clear(File file) {
        if (file == null || !file.exists()) {
            return;
        }
        if (file.isDirectory()) {
            File[] children = file.listFiles();
            if (children != null) {
                for (File child : children) {
                    clear(child);
                }
            }
        }
        file.delete();
    }
}