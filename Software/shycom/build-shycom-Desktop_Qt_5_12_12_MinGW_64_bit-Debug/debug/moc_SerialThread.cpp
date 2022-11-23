/****************************************************************************
** Meta object code from reading C++ file 'SerialThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../shycom/SerialThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialThread_t {
    QByteArrayData data[11];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialThread_t qt_meta_stringdata_SerialThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SerialThread"
QT_MOC_LITERAL(1, 13, 19), // "signalSendModelPose"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "const float*"
QT_MOC_LITERAL(4, 47, 1), // "q"
QT_MOC_LITERAL(5, 49, 20), // "signalSendCurvePoint"
QT_MOC_LITERAL(6, 70, 3), // "qba"
QT_MOC_LITERAL(7, 74, 24), // "signalSendSquareWaveFreq"
QT_MOC_LITERAL(8, 99, 15), // "const uint16_t*"
QT_MOC_LITERAL(9, 115, 1), // "f"
QT_MOC_LITERAL(10, 117, 20) // "slotReceiveSerialBuf"

    },
    "SerialThread\0signalSendModelPose\0\0"
    "const float*\0q\0signalSendCurvePoint\0"
    "qba\0signalSendSquareWaveFreq\0"
    "const uint16_t*\0f\0slotReceiveSerialBuf"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       7,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    6,

       0        // eod
};

void SerialThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendModelPose((*reinterpret_cast< const float*(*)>(_a[1]))); break;
        case 1: _t->signalSendCurvePoint((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->signalSendSquareWaveFreq((*reinterpret_cast< const uint16_t*(*)>(_a[1]))); break;
        case 3: _t->slotReceiveSerialBuf((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialThread::*)(const float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::signalSendModelPose)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::signalSendCurvePoint)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)(const uint16_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::signalSendSquareWaveFreq)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SerialThread.data,
    qt_meta_data_SerialThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SerialThread::signalSendModelPose(const float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialThread::signalSendCurvePoint(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SerialThread::signalSendSquareWaveFreq(const uint16_t * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
