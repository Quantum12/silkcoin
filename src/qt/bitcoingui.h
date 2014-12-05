#ifndef BITCOINGUI_H
#define BITCOINGUI_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class TransactionTableModel;
class ClientModel;
class WalletModel;
class MessageModel;
class TransactionView;
class OverviewPage;
class StatisticsPage;
class BlockBrowser;
class AddressBookPage;
class MessagePage;
class SendCoinsDialog;
class SignVerifyMessageDialog;
class Notificator;
class RPCConsole;
class ChatWindow;

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTableView;
class QAbstractItemModel;
class QModelIndex;
class QProgressBar;
class QStackedWidget;
class QUrl;
QT_END_NAMESPACE

extern int convertmode;

/**
Bitcoin GUI main class. This class represents the main window of the Bitcoin UI. It communicates with both the client and
wallet models to give the user an up-to-date view of the current core state.
*/
class BitcoinGUI : public QMainWindow {
    Q_OBJECT
  public:
    explicit BitcoinGUI(QWidget *parent = 0);
    ~BitcoinGUI();

    /** Set the client model.
    The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel *clientModel);
    /** Set the wallet model.
    The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
    functionality.
    */
    void setWalletModel(WalletModel *walletModel);
    /** Set the message model.
        The message model represents encryption message database, and offers access to the list of messages, address book and sending
        functionality.
    */
    void setMessageModel(MessageModel *messageModel);

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

  private:
    ClientModel *clientModel;
    WalletModel *walletModel;
    MessageModel *messageModel;

    QStackedWidget *centralWidget;

    OverviewPage *overviewPage;
    StatisticsPage *statisticsPage;
    BlockBrowser *blockBrowser;
    ChatWindow *chatWindow;
    QWidget *transactionsPage;
    AddressBookPage *addressBookPage;
    AddressBookPage *receiveCoinsPage;
    MessagePage *messagePage;
    SendCoinsDialog *sendCoinsPage;
    SignVerifyMessageDialog *signVerifyMessageDialog;
    QWidget *settingsPage;
    QWidget *wId;
    QWidget *wId2;

    QLabel *labelEncryptionIcon;
    QLabel *labelStakingIcon;
    QLabel *labelConnectionsIcon;
    QLabel *lblBlockStatus;
    QAction *actionConvertCurrency;
    QLabel *labelHomepage;
    QLabel *progressBarLabel;
    QProgressBar *progressBar;

    QMenuBar *appMenuBar;
    QAction *overviewAction;
    QAction *statisticsAction;
    QAction *blockAction;
    QAction *chatAction;
    QAction *historyAction;
    QAction *quitAction;
    QAction *exitAction;
    QAction *messageAction;
    QAction *settingsAction;
    QAction *sendAction;
    QAction *sendCoinsAction;
    QAction *addressBookAction;
    QAction *signMessageAction;
    QAction *verifyMessageAction;
    QAction *signMessageAction2;
    QAction *verifyMessageAction2;
    QAction *aboutSettingsAction;
    QAction *tutoStackAction;
    QAction *tutoWriteAction;
    QAction *aboutAction;
    QAction *hideAction;
    QAction *receiveCoinsAction;
    QAction *optionsAction;
    QAction *toggleHideAction;
    QAction *exportAction;
    QAction *encryptWalletAction;
    QAction *backupWalletAction;
    QAction *changePassphraseAction;
    QAction *actionLockUnlockWallet_Toolbar;
    QAction *actionLockUnlockWallet_ActionScreen;
    QAction *actionSendReceive;
    QAction *aboutQtAction;
    QAction *openRPCConsoleAction;
    QAction *openRPCConsoleAction2;

    QSystemTrayIcon *trayIcon;
    Notificator *notificator;
    TransactionView *transactionView;
    RPCConsole *rpcConsole;

    QMovie *gifSyncing;
    QMovie *gifCamelLocked;
    QMovie *gifCamelUnlocked;
    QLabel *lblCamelTraveling;

    /** Create the main UI actions. */
    void createActions();
    /** Create the toolbars */
    void createToolBars();
    /** Create system tray (notification) icon */
    void createTrayIcon();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

  public slots:
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count, int nTotalBlocks);
    /** Set the encryption status as shown in the UI.
    @param[in] status            current encryption status
    @see WalletModel::EncryptionStatus
    */
    void setEncryptionStatus(int status);

    /** Notify the user of an error in the network or transaction handling code. */
    void error(const QString &title, const QString &message, bool modal);
    /** Asks the user whether to pay the transaction fee or to cancel the transaction.
    It is currently not possible to pass a return value to another thread through
    BlockingQueuedConnection, so an indirected pointer is used.
    https://bugreports.qt-project.org/browse/QTBUG-10440

    @param[in] nFeeRequired       the required fee
    @param[out] payFee            true to pay the fee, false to not pay the fee
    */
    void askFee(qint64 nFeeRequired, bool *payFee);
    void handleURI(QString strURI);

  private slots:
    void gotoOverviewPage();
    void gotoStatisticsPage();
    void gotoBlockBrowser();
    void gotoHistoryPage();
    void gotoAddressBookPage();
    void gotoReceiveCoinsPage();
    void gotoSendCoinsPage();
    /** Switch to message page */
    void gotoMessagePage();
    void gotoSettingsPage();

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");

    /** Show configuration dialog */
    void optionsClicked();
    void tutoStackClicked();
    void tutoWriteClicked();
    /** Show about dialog */
    void aboutClicked();
#ifndef Q_OS_MAC
    /** Handle tray icon clicked */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
#endif
    /** Show incoming transaction notification for new transactions.

    The new items are those between start and end inclusive, under the given parent item.
    */
    void incomingTransaction(const QModelIndex & parent, int start, int end);

    /** Show incoming message notification for new messages.

        The new items are those between start and end inclusive, under the given parent item.
    */
    void incomingMessage(const QModelIndex & parent, int start, int end);

    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();

    /** Ask for passphrase to unlock wallet temporarily */
    void lockUnlockWallet(void);

    /** Show window if hidden, unminimize when minimized, rise when obscured or show if hidden and fToggleHidden is true */
    void showNormalIfMinimized(bool toTray = false, bool isToggle = false);

    /** simply calls showNormalIfMinimized(true) for use in SLOT() macro */
    void toggleHidden();
    void quitApplication();

    void updateStakingIcon();

};

#endif
