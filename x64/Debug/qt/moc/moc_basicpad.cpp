/****************************************************************************
** Meta object code from reading C++ file 'basicpad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../basicpad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicpad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BasicPad_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BasicPad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BasicPad_t qt_meta_stringdata_BasicPad = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BasicPad"
QT_MOC_LITERAL(1, 9, 12), // "digitClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "digit"
QT_MOC_LITERAL(4, 29, 15), // "operatorClicked"
QT_MOC_LITERAL(5, 45, 2), // "op"
QT_MOC_LITERAL(6, 48, 12), // "equalClicked"
QT_MOC_LITERAL(7, 61, 14), // "controlClicked"
QT_MOC_LITERAL(8, 76, 3) // "cmd"

    },
    "BasicPad\0digitClicked\0\0digit\0"
    "operatorClicked\0op\0equalClicked\0"
    "controlClicked\0cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasicPad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    0,   40,    2, 0x06 /* Public */,
       7,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void BasicPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BasicPad *_t = static_cast<BasicPad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->digitClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->operatorClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->equalClicked(); break;
        case 3: _t->controlClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (BasicPad::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BasicPad::digitClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BasicPad::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BasicPad::operatorClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (BasicPad::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BasicPad::equalClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (BasicPad::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BasicPad::controlClicked)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject BasicPad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BasicPad.data,
      qt_meta_data_BasicPad,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BasicPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasicPad::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BasicPad.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BasicPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void BasicPad::digitClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BasicPad::operatorClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BasicPad::equalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BasicPad::controlClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
