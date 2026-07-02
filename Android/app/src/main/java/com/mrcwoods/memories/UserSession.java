package com.mrcwoods.memories;

import org.json.JSONObject;

public class UserSession {
    public String accessToken;
    public String sub;
    public String qq;
    public String username;
    public String tenantName;
    public String tenantSlug;

    public boolean isLoggedIn() {
        return accessToken != null && !accessToken.isEmpty();
    }

    public JSONObject toJson() {
        JSONObject json = new JSONObject();
        try {
            json.put("accessToken", accessToken);
            json.put("sub", sub);
            json.put("qq", qq);
            json.put("username", username);
            json.put("tenantName", tenantName);
            json.put("tenantSlug", tenantSlug);
        } catch (Exception ignored) {
        }
        return json;
    }

    public static UserSession fromJson(JSONObject json) {
        UserSession session = new UserSession();
        session.accessToken = json.optString("accessToken", "");
        session.sub = json.optString("sub", "");
        session.qq = json.optString("qq", "");
        session.username = json.optString("username", "");
        session.tenantName = json.optString("tenantName", "");
        session.tenantSlug = json.optString("tenantSlug", "");
        return session;
    }
}