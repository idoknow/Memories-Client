import React, { createContext, useContext, useEffect, useState } from 'react';
import type { AppSettings, AppTheme, AppMode, FontFamily } from '@/types';
import { DEFAULT_SETTINGS } from '@/types';

interface SettingsContextValue extends AppSettings {
  setTheme: (theme: AppTheme) => void;
  setMode: (mode: AppMode) => void;
  setFont: (font: FontFamily) => void;
  setFontScale: (scale: number) => void;
  themeLabel: string;
}

const SETTINGS_KEY = 'ios-gallery-settings-v1';

const themeLabels: Record<AppTheme, string> = {
  minimal: '简约黑白',
  moss: '苔光晨雾',
  sunset: '霞橙晴空',
  cyan: '青蓝玻璃',
  neon: '夜航霓光',
};

const fontMap: Record<FontFamily, { family: string; url?: string; injectStyle?: string }> = {
  system: { family: '-apple-system, BlinkMacSystemFont, "SF Pro Text", "Segoe UI", "PingFang SC", "Microsoft YaHei", sans-serif' },
  'noto-sans': {
    family: '"Noto Sans SC", sans-serif',
    url: 'https://fonts.googleapis.com/css2?family=Noto+Sans+SC:wght@400;500;600;700&display=swap',
  },
  'noto-serif': {
    family: '"Noto Serif SC", serif',
    url: 'https://fonts.googleapis.com/css2?family=Noto+Serif+SC:wght@400;600;700&display=swap',
  },
  lxgw: {
    family: '"LXGW WenKai", "PingFang SC", sans-serif',
    url: 'https://cdn.jsdelivr.net/npm/lxgw-wenkai-webfont@1.7.0/style.css',
  },
  alibabapuhuiti: {
    family: '"Alibaba PuHuiTi 2.0", "PingFang SC", sans-serif',
    url: 'https://cdn.jsdelivr.net/npm/alibaba-puhuiti-2/Alibaba-PuHuiTi-Bold/Alibaba-PuHuiTi-Bold.css',
  },
  zpix: {
    family: '"Zpix", monospace',
    url: 'https://cdn.jsdelivr.net/npm/zpix-pixel-font/fonts/stylesheet.css',
  },
  opposans: {
    family: '"OPPO Sans", "PingFang SC", sans-serif',
    injectStyle: `
      @font-face {
        font-family: 'OPPO Sans';
        src: url('https://statics.moonshot.cn/kimi-poster/font/OPPOSans/OPPO-Sans-Regular.woff2') format('woff2');
        font-weight: 400;
        font-style: normal;
        font-display: swap;
      }
    `,
  },
};

const SettingsContext = createContext<SettingsContextValue | undefined>(undefined);

function loadFontCSS(font: FontFamily) {
  const config = fontMap[font];
  if (!config) return;

  const id = `font-css-${font}`;
  if (document.getElementById(id)) return;

  if (config.injectStyle) {
    const style = document.createElement('style');
    style.id = id;
    style.textContent = config.injectStyle;
    document.head.appendChild(style);
    return;
  }

  if (config.url) {
    const link = document.createElement('link');
    link.id = id;
    link.rel = 'stylesheet';
    link.href = config.url;
    link.crossOrigin = 'anonymous';
    document.head.appendChild(link);
  }
}

function applySettings(settings: AppSettings) {
  const html = document.documentElement;

  html.classList.remove('theme-minimal', 'theme-moss', 'theme-sunset', 'theme-cyan', 'theme-neon', 'dark');
  html.classList.add(`theme-${settings.theme}`);
  if (settings.mode === 'dark') {
    html.classList.add('dark');
  }

  html.style.setProperty('--font-scale', String(settings.fontScale));

  const config = fontMap[settings.font];
  document.body.style.fontFamily = config.family;
  loadFontCSS(settings.font);
}

function loadSettings(): AppSettings {
  try {
    const raw = localStorage.getItem(SETTINGS_KEY);
    if (raw) {
      const parsed = JSON.parse(raw) as Partial<AppSettings>;
      return { ...DEFAULT_SETTINGS, ...parsed };
    }
  } catch {
    // 忽略读取错误
  }
  return DEFAULT_SETTINGS;
}

function saveSettings(settings: AppSettings) {
  try {
    localStorage.setItem(SETTINGS_KEY, JSON.stringify(settings));
  } catch {
    // 忽略写入错误
  }
}

export const SettingsProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [settings, setSettings] = useState<AppSettings>(loadSettings);

  useEffect(() => {
    applySettings(settings);
    saveSettings(settings);
  }, [settings]);

  const value: SettingsContextValue = {
    ...settings,
    themeLabel: themeLabels[settings.theme],
    setTheme: (theme) => setSettings((s) => ({ ...s, theme })),
    setMode: (mode) => setSettings((s) => ({ ...s, mode })),
    setFont: (font) => setSettings((s) => ({ ...s, font })),
    setFontScale: (fontScale) => setSettings((s) => ({ ...s, fontScale })),
  };

  return <SettingsContext.Provider value={value}>{children}</SettingsContext.Provider>;
};

export function useSettings(): SettingsContextValue {
  const context = useContext(SettingsContext);
  if (!context) {
    throw new Error('useSettings 必须在 SettingsProvider 内使用');
  }
  return context;
}
