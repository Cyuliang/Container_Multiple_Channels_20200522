/****************************************************************************
** Meta object code from reading C++ file 'setting_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Container_Multiple_Channels_20200522/Main/Setting/setting_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setting_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Setting_Form_t {
    QByteArrayData data[16];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Setting_Form_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Setting_Form_t qt_meta_stringdata_Setting_Form = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Setting_Form"
QT_MOC_LITERAL(1, 13, 20), // "writeParameterSignal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 28), // "initializesTheDeviceListSlot"
QT_MOC_LITERAL(4, 64, 5), // "count"
QT_MOC_LITERAL(5, 70, 9), // "rowLabels"
QT_MOC_LITERAL(6, 80, 29), // "on_channel_pushButton_clicked"
QT_MOC_LITERAL(7, 110, 28), // "on_system_pushButton_clicked"
QT_MOC_LITERAL(8, 139, 31), // "on_listWidget_currentRowChanged"
QT_MOC_LITERAL(9, 171, 10), // "currentRow"
QT_MOC_LITERAL(10, 182, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(11, 203, 16), // "QAbstractButton*"
QT_MOC_LITERAL(12, 220, 6), // "button"
QT_MOC_LITERAL(13, 227, 18), // "automaticStateSlot"
QT_MOC_LITERAL(14, 246, 6), // "status"
QT_MOC_LITERAL(15, 253, 38) // "initializesTheDeviceTemporary..."

    },
    "Setting_Form\0writeParameterSignal\0\0"
    "initializesTheDeviceListSlot\0count\0"
    "rowLabels\0on_channel_pushButton_clicked\0"
    "on_system_pushButton_clicked\0"
    "on_listWidget_currentRowChanged\0"
    "currentRow\0on_buttonBox_clicked\0"
    "QAbstractButton*\0button\0automaticStateSlot\0"
    "status\0initializesTheDeviceTemporaryTableSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Setting_Form[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   55,    2, 0x08 /* Private */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      15,    2,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Bool,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QStringList,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::QStringList,    4,    5,

       0        // eod
};

void Setting_Form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Setting_Form *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->writeParameterSignal();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->initializesTheDeviceListSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 2: _t->on_channel_pushButton_clicked(); break;
        case 3: _t->on_system_pushButton_clicked(); break;
        case 4: _t->on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 6: _t->automaticStateSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->initializesTheDeviceTemporaryTableSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = bool (Setting_Form::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Setting_Form::writeParameterSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Setting_Form::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Setting_Form.data,
    qt_meta_data_Setting_Form,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Setting_Form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Setting_Form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Setting_Form.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Setting_Form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
bool Setting_Form::writeParameterSignal()
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
