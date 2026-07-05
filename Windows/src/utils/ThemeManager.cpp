#include "utils/ThemeManager.h"
#include <QFile>
#include <QTextStream>

ThemeManager& ThemeManager::instance() {
    static ThemeManager inst;
    return inst;
}

ThemeManager::ThemeManager() {
    initThemes();
    m_current = "mint";
}

void ThemeManager::initThemes() {
    m_themes["mint"] = {
        "薄荷绿", "#f0faf5", "#e8f5ed",
        "rgba(255,255,255,0.95)", "rgba(255,255,255,0.90)", "16px",
        "#0f172a", "#334155", "#94a3b8",
        "#1D6E5A", "#175A48", "rgba(29,110,90,0.10)", "#38BDF8", "#F59E0B",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#f8fafc",
        "#fdfcfb", "#e8e3de"
    };

    m_themes["rose"] = {
        "玫瑰粉", "#fef5f7", "#fce4ec",
        "rgba(255,255,255,0.95)", "rgba(255,240,242,0.90)", "16px",
        "#2d1b1e", "#5c3b3f", "#b08d91",
        "#C44569", "#a83655", "rgba(196,69,105,0.10)", "#60A5FA", "#F97316",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#fef5f7",
        "#fdfcfb", "#f0e4e6"
    };

    m_themes["sky"] = {
        "天空蓝", "#f0f7ff", "#e3f0fd",
        "rgba(255,255,255,0.95)", "rgba(240,246,255,0.90)", "16px",
        "#0f172a", "#1e3a5f", "#7b93b0",
        "#2563EB", "#1d4ed8", "rgba(37,99,235,0.10)", "#14B8A6", "#F59E0B",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#f0f7ff",
        "#f8fafd", "#e8eef8"
    };

    m_themes["lavender"] = {
        "薰衣草紫", "#f8f6ff", "#ede9fe",
        "rgba(255,255,255,0.95)", "rgba(245,243,255,0.90)", "16px",
        "#1e1b4b", "#3b3670", "#9d99c7",
        "#7C3AED", "#6d28d9", "rgba(124,58,237,0.10)", "#06B6D4", "#F43F5E",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#f8f6ff",
        "#fdfbff", "#edeaf5"
    };

    m_themes["sunset"] = {
        "日落橙", "#fffaf5", "#fff3e4",
        "rgba(255,255,255,0.95)", "rgba(255,248,240,0.90)", "16px",
        "#2d1a0f", "#5c3a22", "#b09078",
        "#EA580C", "#c2410a", "rgba(234,88,12,0.10)", "#0EA5E9", "#EAB308",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#fffaf5",
        "#fdfaf7", "#f0e8dd"
    };

    m_themes["ocean"] = {
        "深海蓝", "#f2f9fa", "#e4f3f5",
        "rgba(255,255,255,0.95)", "rgba(235,248,250,0.90)", "16px",
        "#0f282d", "#1e4d56", "#6b99a2",
        "#0D9488", "#0f766e", "rgba(13,148,136,0.10)", "#2563EB", "#F97316",
        "#ffffff", "#ffffff",
        "#ffffff", "#ffffff",
        "#ffffff", "#f2f9fa",
        "#f8fcfd", "#e4eff2"
    };

    m_themes["dark"] = {
        "深色暗夜", "#0f172a", "#1e293b",
        "rgba(30,41,59,0.95)", "rgba(15,23,42,0.90)", "16px",
        "#e2e8f0", "#94a3b8", "#64748b",
        "#53C49E", "#1D6E5A", "rgba(83,196,158,0.15)", "#38BDF8", "#F59E0B",
        "#1e293b", "#0f172a",
        "#1e293b", "#0f172a",
        "#334155", "#1e293b",
        "#1e293b", "#0f172a"
    };
}

void ThemeManager::setTheme(const QString& name) {
    if (m_themes.contains(name)) {
        m_current = name;
    }
}

QString ThemeManager::currentTheme() const { return m_current; }

QStringList ThemeManager::themeNames() const {
    QStringList names;
    for (auto it = m_themes.begin(); it != m_themes.end(); ++it)
        names.append(it.key());
    return names;
}

const ThemeColors& ThemeManager::current() const {
    static ThemeColors fallback;
    auto it = m_themes.constFind(m_current);
    return it != m_themes.constEnd() ? *it : fallback;
}

QStringList ThemeManager::fontPresets() {
    return {
        "system", "noto", "wenquanyi", "source-han", "pingfang", "inter", "jetbrains"
    };
}

QString ThemeManager::fontPresetDisplayName(const QString& key) {
    if (key == "system") return "系统默认";
    if (key == "noto") return "Noto Sans SC";
    if (key == "wenquanyi") return "WenQuanYi Micro Hei";
    if (key == "source-han") return "Source Han Sans SC";
    if (key == "pingfang") return "PingFang SC";
    if (key == "inter") return "Inter";
    if (key == "jetbrains") return "JetBrains Mono";
    return key;
}

QString ThemeManager::buildStylesheet(bool) const {
    const auto& c = current();
    bool isDark = (m_current == "dark");

    QString primaryBg = c.bgGradientStart;
    QString secondaryBg = c.bgGradientEnd;
    QString cardBg = c.cardBg;
    QString textPrimary = c.textPrimary;
    QString textSecondary = c.textSecondary;
    QString textMuted = c.textMuted;
    QString accent = c.accent;
    QString accentHover = c.accentHover;
    QString inputBg = isDark ? "#0f172a" : "#ffffff";
    QString inputBorder = isDark ? "#334155" : "#cbd5e1";
    QString borderColor = isDark ? "#334155" : "#94a3b8";
    QString toolbarBg = isDark ? "#1e293b" : "#ffffff";
    QString toolbarBorder = isDark ? "#334155" : "#cbd5e1";
    QString scrollBarBg = isDark ? "#1e293b" : "#e2e8f0";
    QString scrollBarHandle = isDark ? "#475569" : "#94a3b8";
    QString menuBg = isDark ? "#1e293b" : "#ffffff";
    QString menuBorder = isDark ? "#334155" : "#cbd5e1";
    QString hoverBg = isDark ? "#334155" : "#f1f5f9";
    QString pressedBg = isDark ? "#475569" : "#e2e8f0";

    return QString(R"(
* { font-family: "Noto Sans SC", "WenQuanYi Micro Hei", "Sans Serif"; font-size: 13px; color: %1; }
QMainWindow { background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 %2, stop:1 %3); }
QMenuBar { background: %4; border-bottom: 2px solid %5; padding: 6px 12px; font-weight: 600; }
QMenuBar::item { padding: 8px 16px; margin: 2px 4px; border-radius: 8px; color: %6; }
QMenuBar::item:selected { background: %7; color: %8; }
QMenu { background: %9; border: 2px solid %10; border-radius: 12px; padding: 8px; }
QMenu::item { padding: 10px 34px 10px 18px; margin: 2px 6px; border-radius: 8px; color: %6; }
QMenu::item:selected { background: %11; color: %7; }
QToolBar { background: %4; border-bottom: 2px solid %5; padding: 8px 12px; spacing: 10px; }
QToolBar QToolButton { padding: 10px 18px; border-radius: 10px; color: %6; font-weight: 700; border: 2px solid %10; background: %12; }
QToolBar QToolButton:hover { background: %7; border-color: %7; color: %8; }
QPushButton { padding: 10px 24px; border-radius: 10px; font-weight: 700; border: 2px solid transparent; min-height: 24px; }
QPushButton:disabled { color: rgba(100,116,139,0.4); background: %12; border-color: %10; }
QPushButton#primaryBtn, QPushButton[primaryBtn="true"] { background: %7; color: %8; font-weight: 800; border: 2px solid %7; }
QPushButton#primaryBtn:hover, QPushButton[primaryBtn="true"]:hover { background: %13; border-color: %13; }
QPushButton[flat="true"] { background: %12; border: 2px solid %10; color: %6; }
QPushButton[flat="true"]:hover { background: %14; border-color: %7; color: %7; }
QPushButton { background: %12; border: 2px solid %10; color: %1; }
QPushButton:hover { border-color: %7; color: %7; }
QPushButton:pressed { background: %15; }
QLineEdit, QComboBox, QSpinBox { padding: 10px 16px; border-radius: 10px; border: 2px solid %16; background: %17; color: %1; }
QLineEdit:focus, QComboBox:focus, QSpinBox:focus { border-color: %7; }
QComboBox::drop-down { border: none; width: 24px; subcontrol-origin: padding; subcontrol-position: right center; }
QComboBox::down-arrow { width: 10px; height: 10px; }
QComboBox QAbstractItemView { background: %9; border: 2px solid %10; border-radius: 10px; padding: 8px; }
QComboBox QAbstractItemView::item { padding: 10px 16px; border-radius: 8px; color: %1; }
QComboBox QAbstractItemView::item:selected { background: %11; color: %7; }
QGroupBox { background: %12; border: 2px solid %18; border-radius: 16px; margin-top: 24px; padding: 24px 20px 20px; font-weight: 700; color: %1; }
QGroupBox::title { padding: 6px 14px; margin-left: 20px; margin-top: -16px; background: %12; border-radius: 8px; border: 2px solid %18; }
QTabWidget::pane { background: %12; border: 2px solid %18; border-radius: 12px; padding: 16px; }
QTabBar::tab { padding: 10px 24px; margin: 4px 6px; border-radius: 10px; color: %6; font-weight: 500; }
QTabBar::tab:selected { background: %12; color: %7; font-weight: 700; border: 2px solid %18; border-bottom: none; }
QTabBar::tab:hover:!selected { background: %14; color: %1; }
QListWidget { background: %12; border: 2px solid %10; border-radius: 12px; color: %6; padding: 8px; outline: none; }
QListWidget::item { padding: 12px 16px; margin: 3px 6px; border-radius: 10px; }
QListWidget::item:hover { background: %14; }
QListWidget::item:selected { background: %11; color: %7; }
QScrollBar:vertical { background: %19; width: 10px; border-radius: 5px; margin: 4px 0; }
QScrollBar::handle:vertical { background: %20; border-radius: 5px; min-height: 40px; }
QScrollBar::handle:vertical:hover { background: %6; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; border: none; }
QScrollBar:horizontal { background: %19; height: 10px; border-radius: 5px; margin: 0 4px; }
QScrollBar::handle:horizontal { background: %20; border-radius: 5px; min-width: 40px; }
QLabel[galleryState="true"] { color: %6; font-size: 16px; font-weight: 600; padding: 24px; }
QLabel[galleryMeta="true"] { color: %6; font-size: 12px; font-weight: 700; padding: 0 6px; }
QToolButton[galleryThumb="true"] { background: %12; border-radius: 12px; border: 2px solid %10; padding: 6px; }
QToolButton[galleryThumb="true"]:hover { background: %14; border-color: %7; }
QToolButton[galleryThumb="true"][selected="true"] { background: %11; border: 3px solid %7; }
QProgressBar { min-height: 12px; max-height: 12px; border-radius: 6px; border: 2px solid %10; background: %12; }
QProgressBar::chunk { border-radius: 6px; background: %7; }
QDialog { background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 %21, stop:1 %22); border: 2px solid %18; border-radius: 16px; }
QToolTip { background: %12; color: %1; border: 2px solid %10; border-radius: 10px; padding: 8px 14px; }
QStatusBar { background: %4; border-top: 2px solid %5; color: %6; padding: 6px 14px; }
QLabel[statusText="true"] { color: %6; font-size: 12px; }
QLabel[statusPill="checking"] { color: #FBBF24; background: rgba(251,191,36,0.15); border: 2px solid rgba(251,191,36,0.4); border-radius: 10px; padding: 4px 12px; font-weight: 700; }
QLabel[statusPill="ok"] { color: %7; background: rgba(83,196,158,0.15); border: 2px solid rgba(83,196,158,0.4); border-radius: 10px; padding: 4px 12px; font-weight: 700; }
QLabel[statusPill="error"] { color: #FB7185; background: rgba(251,113,133,0.15); border: 2px solid rgba(251,113,133,0.4); border-radius: 10px; padding: 4px 12px; font-weight: 700; }
QTextEdit { background: %12; border: 2px solid %10; border-radius: 12px; padding: 14px 18px; color: %6; }
QCheckBox { spacing: 12px; color: %6; font-size: 13px; }
QCheckBox::indicator { width: 22px; height: 22px; border-radius: 6px; border: 2px solid %16; background: %17; }
QCheckBox::indicator:checked { background: %7; border-color: %7; }
QLabel[heading="true"] { font-weight: 700; font-size: 20px; color: %1; }
QLabel[subtitle="true"] { font-size: 12px; color: %6; }
QLabel#appTitle { font-weight: 800; font-size: 32px; color: %1; }
)"
    ).arg(textPrimary, primaryBg, secondaryBg,
          toolbarBg, toolbarBorder, textSecondary,
          accent, "#ffffff", menuBg, menuBorder,
          c.accentLight, inputBg, accentHover,
          hoverBg, pressedBg, inputBorder,
          inputBg, borderColor, scrollBarBg,
          scrollBarHandle, c.dialogBgStart, c.dialogBgEnd);
}
