/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../shycom/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 31), // "slotSerialActionDockwidgetClose"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 30), // "slotCurveActionDockwidgetClose"
QT_MOC_LITERAL(4, 75, 30), // "slotMotorActionDockwidgetClose"
QT_MOC_LITERAL(5, 106, 7), // "uint8_t"
QT_MOC_LITERAL(6, 114, 2), // "id"
QT_MOC_LITERAL(7, 117, 17), // "slotAddMotorItem0"
QT_MOC_LITERAL(8, 135, 17), // "slotAddMotorItem1"
QT_MOC_LITERAL(9, 153, 17), // "slotAddMotorItem2"
QT_MOC_LITERAL(10, 171, 17), // "slotAddMotorItem3"
QT_MOC_LITERAL(11, 189, 17), // "initGuiMotorBase0"
QT_MOC_LITERAL(12, 207, 17), // "initGuiMotorBase1"
QT_MOC_LITERAL(13, 225, 17), // "initGuiMotorBase2"
QT_MOC_LITERAL(14, 243, 17), // "initGuiMotorBase3"
QT_MOC_LITERAL(15, 261, 31), // "slotMotorActionDockwidgetClose0"
QT_MOC_LITERAL(16, 293, 31), // "slotMotorActionDockwidgetClose1"
QT_MOC_LITERAL(17, 325, 31), // "slotMotorActionDockwidgetClose2"
QT_MOC_LITERAL(18, 357, 31) // "slotMotorActionDockwidgetClose3"

    },
    "MainWindow\0slotSerialActionDockwidgetClose\0"
    "\0slotCurveActionDockwidgetClose\0"
    "slotMotorActionDockwidgetClose\0uint8_t\0"
    "id\0slotAddMotorItem0\0slotAddMotorItem1\0"
    "slotAddMotorItem2\0slotAddMotorItem3\0"
    "initGuiMotorBase0\0initGuiMotorBase1\0"
    "initGuiMotorBase2\0initGuiMotorBase3\0"
    "slotMotorActionDockwidgetClose0\0"
    "slotMotorActionDockwidgetClose1\0"
    "slotMotorActionDockwidgetClose2\0"
    "slotMotorActionDockwidgetClose3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    1,   91,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSerialActionDockwidgetClose(); break;
        case 1: _t->slotCurveActionDockwidgetClose(); break;
        case 2: _t->slotMotorActionDockwidgetClose((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 3: _t->slotAddMotorItem0(); break;
        case 4: _t->slotAddMotorItem1(); break;
        case 5: _t->slotAddMotorItem2(); break;
        case 6: _t->slotAddMotorItem3(); break;
        case 7: _t->initGuiMotorBase0(); break;
        case 8: _t->initGuiMotorBase1(); break;
        case 9: _t->initGuiMotorBase2(); break;
        case 10: _t->initGuiMotorBase3(); break;
        case 11: _t->slotMotorActionDockwidgetClose0(); break;
        case 12: _t->slotMotorActionDockwidgetClose1(); break;
        case 13: _t->slotMotorActionDockwidgetClose2(); break;
        case 14: _t->slotMotorActionDockwidgetClose3(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
