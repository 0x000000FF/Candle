// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QTimer>
#include <QBasicTimer>
#include <QStringList>
#include <QList>
#include <QTime>
#include <QMenu>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "gcodeviewparse.h"
#include "origindrawer.h"
#include "gcodedrawer.h"
#include "tooldrawer.h"
#include "heightmapborderdrawer.h"
#include "heightmapgriddrawer.h"
#include "heightmapinterpolationdrawer.h"
#include "shaderdrawable.h"
#include "gcodetablemodel.h"
#include "heightmaptablemodel.h"
#include "frmsettings.h"
#include "frmabout.h"
#include "styledtoolbutton.h"
#include "interpolation.h"

#ifdef WINDOWS
    #include <QtWinExtras/QtWinExtras>
    #include "shobjidl.h"
#endif

namespace Ui {
class frmMain;
}

struct CommandAttributes {
    int length;
    int consoleIndex;
    int tableIndex;
    QString command;
};

struct CommandQueue {
    QString command;
    int tableIndex;
    bool showInConsole;
};

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();    

    double toolZPosition();

private slots:    
    void updateHeightMapInterpolationDrawer(bool reset = false);
    void placeVisualizerButtons();

    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);
    void onTimerConnection();
    void onTimerStateQuery();
    void onCmdJogStepClicked();
    void onVisualizatorRotationChanged();
    void onScroolBarAction(int action);
    void onJogTimer();
    void onTableInsertLine();
    void onTableDeleteLines();
    void onActRecentFileTriggered();
    void onCboCommandReturnPressed();
    void onTableCurrentChanged(QModelIndex idx1, QModelIndex idx2);
    void onConsoleMouseMove(int dx, int dy);
    void onConsoleMousePress();

    void on_actFileExit_triggered();
    void on_cmdFileOpen_clicked();        
    void on_cmdFit_clicked();
    void on_cmdFileSend_clicked();
    void onTableCellChanged(QModelIndex i1, QModelIndex i2);
    void on_actServiceSettings_triggered();
    void on_actFileOpen_triggered();
    void on_cmdCommandSend_clicked();
    void on_cmdHome_clicked();
    void on_cmdTouch_clicked();
    void on_cmdZeroXY_clicked();
    void on_cmdZeroZ_clicked();
    void on_cmdReturnXY_clicked();
    void on_cmdReset_clicked();
    void on_cmdUnlock_clicked();
    void on_cmdTopZ_clicked();
    void on_cmdSpindle_toggled(bool checked);
    void on_txtSpindleSpeed_editingFinished();
    void on_sliSpindleSpeed_valueChanged(int value);
    void on_cmdYPlus_clicked();
    void on_cmdYMinus_clicked();
    void on_cmdXPlus_clicked();
    void on_cmdXMinus_clicked();
    void on_cmdZPlus_clicked();
    void on_cmdZMinus_clicked();
    void on_chkTestMode_clicked(bool checked);
    void on_cmdFilePause_clicked(bool checked);
    void on_cmdFileReset_clicked();
    void on_actFileNew_triggered();
    void on_cmdClearConsole_clicked();
    void on_actFileSaveAs_triggered();
    void on_actFileSave_triggered();
    void on_cmdTop_clicked();
    void on_cmdFront_clicked();
    void on_cmdLeft_clicked();
    void on_cmdIsometric_clicked();
    void on_actAbout_triggered();
    void on_txtFeed_editingFinished();
    void on_sliFeed_valueChanged(int value);
    void on_chkFeedOverride_toggled(bool checked);
    void on_grpFeed_toggled(bool checked);
    void on_grpSpindle_toggled(bool checked);
    void on_grpJog_toggled(bool checked);
    void on_chkKeyboardControl_toggled(bool checked);
    void on_tblProgram_customContextMenuRequested(const QPoint &pos);
    void on_splitter_splitterMoved(int pos, int index);
    void on_actRecentClear_triggered();
    void on_grpHeightMap_toggled(bool arg1);
    void on_chkHeightMapBorderShow_toggled(bool checked);
    void on_txtHeightMapBorderX_valueChanged(double arg1);
    void on_txtHeightMapBorderWidth_valueChanged(double arg1);
    void on_txtHeightMapBorderY_valueChanged(double arg1);
    void on_txtHeightMapBorderHeight_valueChanged(double arg1);
    void on_chkHeightMapGridShow_toggled(bool checked);
    void on_txtHeightMapGridX_valueChanged(double arg1);
    void on_txtHeightMapGridY_valueChanged(double arg1);
    void on_txtHeightMapGridZBottom_valueChanged(double arg1);
    void on_txtHeightMapGridZTop_valueChanged(double arg1);
    void on_cmdHeightMapMode_toggled(bool checked);
    void on_chkHeightMapInterpolationShow_toggled(bool checked);
    void on_cmdHeightMapLoad_clicked();
    void on_txtHeightMapInterpolationStepX_valueChanged(double arg1);
    void on_txtHeightMapInterpolationStepY_valueChanged(double arg1);
    void on_chkHeightMapUse_clicked(bool checked);
    void on_cmdHeightMapCreate_clicked();
    void on_cmdHeightMapBorderAuto_clicked();

    void on_cmdFileAbort_clicked();

protected:
    void showEvent(QShowEvent *se);
    void hideEvent(QHideEvent *he);
    void resizeEvent(QResizeEvent *re);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *ce);
    void dragEnterEvent(QDragEnterEvent *dee);
    void dropEvent(QDropEvent *de);

private:
    const int BUFFERLENGTH = 127;

    Ui::frmMain *ui;
    GcodeViewParse m_viewParser;
    GcodeViewParse m_probeParser;

    OriginDrawer *m_originDrawer;

    GcodeDrawer *m_codeDrawer;
    GcodeDrawer *m_probeDrawer;
    GcodeDrawer *m_currentDrawer;

    ToolDrawer m_toolDrawer;
    HeightMapBorderDrawer m_heightMapBorderDrawer;
    HeightMapGridDrawer m_heightMapGridDrawer;
    HeightMapInterpolationDrawer m_heightMapInterpolationDrawer;

    GCodeTableModel m_programModel;
    GCodeTableModel m_probeModel;
    GCodeTableModel m_programHeightmapModel;

    HeightMapTableModel m_heightMapModel;

    bool m_programLoading;
    bool m_settingsLoading;

    QSerialPort m_serialPort;

    frmSettings m_settings;
    frmAbout m_frmAbout;

    QString m_settingsFileName;
    QString m_programFileName;
    QString m_heightMapFileName;

    bool m_fileChanged = false;
    bool m_heightMapChanged = false;

    QTimer m_timerConnection;
    QTimer m_timerStateQuery;
    QBasicTimer m_timerToolAnimation;

    QStringList m_status;
    QStringList m_statusCaptions;
    QStringList m_statusBackColors;
    QStringList m_statusForeColors;

#ifdef WINDOWS
    QWinTaskbarButton *m_taskBarButton;
    QWinTaskbarProgress *m_taskBarProgress;
#endif

    QMenu *m_tableMenu;
    QList<CommandAttributes> m_commands;
    QList<CommandQueue> m_queue;
    QTime m_startTime;

    double m_storedX = 0;
    double m_storedY = 0;
    double m_storedZ = 0;
    QString m_storedParserStatus;
    double m_storedOffsets[1][3];

    int m_pressedConsoleMinHeight;

    // Flags
    bool m_settingZeroXY = false;
    bool m_settingZeroZ = false;
    bool m_homing = false;
    bool m_programSpeed = false;
    bool m_updateSpindleSpeed = false;
    bool m_updateParserStatus = false;
    bool m_updateFeed = false;

    bool m_reseting = false;
    bool m_resetCompleted = true;
    bool m_aborting = false;

    bool m_processingFile = false;
    bool m_transferCompleted = false;
    bool m_fileEndSent = false;

    bool m_heightMapMode;
    bool m_cellChanged;

    // Indices
    int m_fileCommandIndex;
    int m_fileProcessedCommandIndex;
    int m_probeIndex;

    // Current values
    int m_lastDrawnLineIndex;
    int m_lastGrblStatus;
    double m_originalFeed;

    // Keyboard
    bool m_keyPressed = false;
    bool m_jogBlock = false;
    bool m_absoluteCoordinates;
    bool m_storedKeyboardControl;      

    // Spindle
    bool m_spindleCW = true;
    bool m_spindleCommandSpeed = false;

    QStringList m_recentFiles;
    QStringList m_recentHeightmaps;

    void loadFile(QString fileName);
    void loadFile(QList<QString> data);
    void clearTable();
    void loadSettings();
    void saveSettings();
    bool saveChanges(bool heightMapMode);
    void updateControlsState();
    void openPort();
    void sendCommand(QString command, int tableIndex = -1, bool showInConsole = true);
    void grblReset();
    int bufferLength();
    void sendNextFileCommands();
    void applySettings();
    void updateParser();
    bool dataIsFloating(QString data);
    bool dataIsEnd(QString data);
    bool dataIsReset(QString data);

    QTime updateProgramEstimatedTime(QList<LineSegment *> lines);
    bool saveProgramToFile(QString fileName);
    QString feedOverride(QString command);

    bool eventFilter(QObject *obj, QEvent *event);
    void blockJogForRapidMovement();
    bool keyIsMovement(int key);
    void resizeCheckBoxes();
    void updateLayouts();
    void updateRecentFilesMenu();
    void addRecentFile(QString fileName);
    void addRecentHeightmap(QString fileName);
    double toMetric(double value);

    QRectF borderRectFromTextboxes();
    QRectF borderRectFromExtremes();
    void updateHeightMapBorderDrawer();
    bool updateHeightMapGrid();
    void loadHeightMap(QString fileName);
    bool saveHeightMap(QString fileName);

    GCodeTableModel *m_currentModel;
    QList<LineSegment *> subdivideSegment(LineSegment *segment);
    void resizeTableHeightMapSections();
    void updateHeightMapGrid(double arg1);
    void resetHeightmap();
    void storeParserState();
    void restoreParserState();
    void storeOffsets();
    void restoreOffsets();
    bool isGCodeFile(QString fileName);
    bool isHeightmapFile(QString fileName);
    bool compareCoordinates(double x, double y, double z);
};

#endif // FRMMAIN_H
