#ifndef APPIMAGEUPDATER_HPP_INCLUDED
#define APPIMAGEUPDATER_HPP_INCLUDED

#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QCloseEvent>
#include <QQueue>
#include <QMessageBox>
#include <QProgressDialog>
#include <QTimer>
#include <QProcess>
#include <QFileInfo>
#include <QSystemTrayIcon>
#include <QDirIterator>
#include <ui_AppImageUpdater.h>
#include <AppImageUpdaterBridge>
#include <AppImageUpdaterDialog>
#include <SettingsDialog.hpp>
#include <AuthorizationDialog.hpp>

class AppImageUpdater : public QWidget
{
    Q_OBJECT
public:
    AppImageUpdater(bool minimized, QWidget *parent = nullptr);
    ~AppImageUpdater();
public Q_SLOTS:
    void gracefulShow(void);
private Q_SLOTS:
    void updateAppImagesInQueue(void);
    void showAbout(void);
    void showHide(void); 
    void showHideWindow(QSystemTrayIcon::ActivationReason);
    void handleAppImageInformation(QJsonObject);
    void handleAuthorizationFinished(QJsonObject);
    void handleFinished(QJsonObject);
    void handleError(short);
    void handleAutoUpdateError(QString, short);
    void handleStarted(void);
    void handleCanceled(void);
Q_SIGNALS:
    void quit();
private:
    SettingsDialog _pSettings;
    AuthorizationDialog _pAuthorizationDialog;
    Ui::MainWidget _pUi;
    QPoint centerPos;
    QAtomicInteger<bool> _bUpdateStarted = false;
    QMessageBox _pAboutMessageBox;
    QString _pCurrentAppImagePath;
    QPixmap _pDropHere,
            _pDropNorm;
    QIcon _pWindowIcon;
    QQueue<QString> _pAppImagePaths;
    AppImageUpdaterBridge::AppImageDeltaRevisioner *m_Updater = nullptr;
    AppImageUpdaterBridge::AppImageUpdaterDialog *_pUpdateDialog = nullptr;
    QSystemTrayIcon *_pTIcon = nullptr;
protected:
    void closeEvent(QCloseEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
};

#endif // APPIMAGEUPDATER_HPP_INCLUDED
