/****************************************************************************
** Meta object code from reading C++ file 'dataprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Container_Multiple_Channels_20200522/Main/DataProcessing/dataprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataProcessing_t {
    QByteArrayData data[20];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataProcessing_t qt_meta_stringdata_DataProcessing = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DataProcessing"
QT_MOC_LITERAL(1, 15, 30), // "signal_InitializationParameter"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 7), // "address"
QT_MOC_LITERAL(4, 55, 4), // "port"
QT_MOC_LITERAL(5, 60, 11), // "serviceType"
QT_MOC_LITERAL(6, 72, 9), // "heartBeat"
QT_MOC_LITERAL(7, 82, 11), // "serviceMode"
QT_MOC_LITERAL(8, 94, 9), // "shortLink"
QT_MOC_LITERAL(9, 104, 17), // "signal_toSendData"
QT_MOC_LITERAL(10, 122, 14), // "channel_number"
QT_MOC_LITERAL(11, 137, 4), // "data"
QT_MOC_LITERAL(12, 142, 14), // "slot_linkState"
QT_MOC_LITERAL(13, 157, 5), // "state"
QT_MOC_LITERAL(14, 163, 17), // "slot_connectCount"
QT_MOC_LITERAL(15, 181, 5), // "count"
QT_MOC_LITERAL(16, 187, 18), // "slot_sendDataToLog"
QT_MOC_LITERAL(17, 206, 6), // "result"
QT_MOC_LITERAL(18, 213, 20), // "slot_containerResult"
QT_MOC_LITERAL(19, 234, 7) // "channel"

    },
    "DataProcessing\0signal_InitializationParameter\0"
    "\0address\0port\0serviceType\0heartBeat\0"
    "serviceMode\0shortLink\0signal_toSendData\0"
    "channel_number\0data\0slot_linkState\0"
    "state\0slot_connectCount\0count\0"
    "slot_sendDataToLog\0result\0"
    "slot_containerResult\0channel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   44,    2, 0x06 /* Public */,
       9,    2,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   62,    2, 0x0a /* Public */,
      14,    1,   67,    2, 0x0a /* Public */,
      16,    2,   70,    2, 0x0a /* Public */,
      18,    2,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort, QMetaType::Int, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   19,   17,

       0        // eod
};

void DataProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_InitializationParameter((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const quint16(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5])),(*reinterpret_cast< const int(*)>(_a[6]))); break;
        case 1: _t->signal_toSendData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->slot_linkState((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->slot_connectCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_sendDataToLog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->slot_containerResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataProcessing::*)(const QString & , const quint16 & , const int & , bool , const int & , const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessing::signal_InitializationParameter)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataProcessing::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessing::signal_toSendData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataProcessing::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataProcessing.data,
    qt_meta_data_DataProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DataProcessing::signal_InitializationParameter(const QString & _t1, const quint16 & _t2, const int & _t3, bool _t4, const int & _t5, const int & _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataProcessing::signal_toSendData(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE