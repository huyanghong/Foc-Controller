/****************************************************************************
** Meta object code from reading C++ file 'myserialwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../shycom/myserialwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myserialwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MySerialWidget_t {
    QByteArrayData data[12];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MySerialWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MySerialWidget_t qt_meta_stringdata_MySerialWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MySerialWidget"
QT_MOC_LITERAL(1, 15, 22), // "signalSerialReceiveBuf"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 3), // "qba"
QT_MOC_LITERAL(4, 43, 14), // "slotSerialSend"
QT_MOC_LITERAL(5, 58, 19), // "slotBtnClearClicked"
QT_MOC_LITERAL(6, 78, 18), // "slotBtnSendClicked"
QT_MOC_LITERAL(7, 97, 20), // "slotUpdateSerialList"
QT_MOC_LITERAL(8, 118, 19), // "slotReadySerialRead"
QT_MOC_LITERAL(9, 138, 21), // "slotOpenOrCloseSerial"
QT_MOC_LITERAL(10, 160, 33), // "slot_cbb_baud_currentIndexCha..."
QT_MOC_LITERAL(11, 194, 22) // "slot_cbb_com_activated"

    },
    "MySerialWidget\0signalSerialReceiveBuf\0"
    "\0qba\0slotSerialSend\0slotBtnClearClicked\0"
    "slotBtnSendClicked\0slotUpdateSerialList\0"
    "slotReadySerialRead\0slotOpenOrCloseSerial\0"
    "slot_cbb_baud_currentIndexChanged\0"
    "slot_cbb_com_activated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MySerialWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   62,    2, 0x0a /* Public */,
       5,    0,   65,    2, 0x0a /* Public */,
       6,    0,   66,    2, 0x0a /* Public */,
       7,    0,   67,    2, 0x0a /* Public */,
       8,    0,   68,    2, 0x0a /* Public */,
       9,    0,   69,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MySerialWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MySerialWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerialReceiveBuf((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->slotSerialSend((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->slotBtnClearClicked(); break;
        case 3: _t->slotBtnSendClicked(); break;
        case 4: _t->slotUpdateSerialList(); break;
        case 5: _t->slotReadySerialRead(); break;
        case 6: _t->slotOpenOrCloseSerial(); break;
        case 7: _t->slot_cbb_baud_currentIndexChanged(); break;
        case 8: _t->slot_cbb_com_activated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MySerialWidget::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySerialWidget::signalSerialReceiveBuf)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MySerialWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MySerialWidget.data,
    qt_meta_data_MySerialWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MySerialWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySerialWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MySerialWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MySerialWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MySerialWidget::signalSerialReceiveBuf(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
