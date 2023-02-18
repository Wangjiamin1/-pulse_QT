/****************************************************************************
** Meta object code from reading C++ file 'ex_qthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ex_qthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ex_qthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EX_QThread_t {
    QByteArrayData data[10];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EX_QThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EX_QThread_t qt_meta_stringdata_EX_QThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "EX_QThread"
QT_MOC_LITERAL(1, 11, 14), // "sendOneSecData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "oneSec_CH1"
QT_MOC_LITERAL(4, 38, 10), // "oneSec_CH2"
QT_MOC_LITERAL(5, 49, 10), // "oneSec_CH3"
QT_MOC_LITERAL(6, 60, 14), // "sendTenSecData"
QT_MOC_LITERAL(7, 75, 10), // "tenSec_CH1"
QT_MOC_LITERAL(8, 86, 10), // "tenSec_CH2"
QT_MOC_LITERAL(9, 97, 10) // "tenSec_CH3"

    },
    "EX_QThread\0sendOneSecData\0\0oneSec_CH1\0"
    "oneSec_CH2\0oneSec_CH3\0sendTenSecData\0"
    "tenSec_CH1\0tenSec_CH2\0tenSec_CH3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EX_QThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       6,    3,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,

       0        // eod
};

void EX_QThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EX_QThread *_t = static_cast<EX_QThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendOneSecData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: _t->sendTenSecData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EX_QThread::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EX_QThread::sendOneSecData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (EX_QThread::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EX_QThread::sendTenSecData)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject EX_QThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_EX_QThread.data,
      qt_meta_data_EX_QThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EX_QThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EX_QThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EX_QThread.stringdata0))
        return static_cast<void*>(const_cast< EX_QThread*>(this));
    return QThread::qt_metacast(_clname);
}

int EX_QThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void EX_QThread::sendOneSecData(double _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EX_QThread::sendTenSecData(double _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
