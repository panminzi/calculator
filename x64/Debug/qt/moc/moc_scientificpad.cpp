/****************************************************************************
** Meta object code from reading C++ file 'scientificpad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../scientificpad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scientificpad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScientificPad_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScientificPad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScientificPad_t qt_meta_stringdata_ScientificPad = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ScientificPad"
QT_MOC_LITERAL(1, 14, 13), // "squareClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "sqrtClicked"
QT_MOC_LITERAL(4, 41, 10) // "absClicked"

    },
    "ScientificPad\0squareClicked\0\0sqrtClicked\0"
    "absClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScientificPad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScientificPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScientificPad *_t = static_cast<ScientificPad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->squareClicked(); break;
        case 1: _t->sqrtClicked(); break;
        case 2: _t->absClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ScientificPad::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScientificPad::squareClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScientificPad::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScientificPad::sqrtClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ScientificPad::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScientificPad::absClicked)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ScientificPad::staticMetaObject = {
    { &BasicPad::staticMetaObject, qt_meta_stringdata_ScientificPad.data,
      qt_meta_data_ScientificPad,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScientificPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScientificPad::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScientificPad.stringdata0))
        return static_cast<void*>(this);
    return BasicPad::qt_metacast(_clname);
}

int ScientificPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicPad::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ScientificPad::squareClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ScientificPad::sqrtClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ScientificPad::absClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
