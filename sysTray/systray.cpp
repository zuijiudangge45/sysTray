#include <QWidget>

#include "sysTray/systray.h"
#include "custommenu.h"

sysTray::sysTray(QWidget *parent) : QSystemTrayIcon(parent), m_parent(parent)
{
    initSystemTray();
    show();
}

sysTray::~sysTray()
{
}

void sysTray::initSystemTray()
{
    setToolTip(QStringLiteral("Application-name"));               //设置菜单名字（我们鼠标移到那时会显示的文字）
    setIcon(QIcon(":/Icon/chips.png"));
    //点击托盘时会触发
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

//添加系统菜单：显示和退出
void sysTray::addSystemTrayMenu()
{
    CustomMenu *customMenu = new CustomMenu(m_parent);
    //onShow可理解为对象名+logo+显示的文字
    customMenu->addCustomMenu("onShow", ":/Icon/message.png", QStringLiteral("显示"));
    customMenu->addCustomMenu("onQuit", ":/Icon/exit.png", QStringLiteral("退出"));
    //如果是"onshow"对象触发到了点击信号则执行onShowNormal槽方法
    connect(customMenu->getAction("onShow"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowNormal(bool)));
    connect(customMenu->getAction("onQuit"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowQuit(bool)));
    customMenu->exec(QCursor::pos());//事件循环接受鼠标操作（如果不加这个那么你右键菜单无效）
    delete customMenu;				 //如果点击了某个菜单项则菜单项释放并且执行操作
    customMenu = nullptr;
}
void sysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {//如果原因是左键点击触发
        m_parent->show();			//将父窗体显示
        m_parent->activateWindow(); //将父窗口设置为活动窗口
    }
    else if (reason == QSystemTrayIcon::Context) {//如果原因是右键点击
        addSystemTrayMenu();					  //添加菜单项
    }
}
