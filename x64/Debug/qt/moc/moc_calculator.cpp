/****************************************************************************
** Meta object code from reading C++ file 'calculator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../calculator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Calculator_t {
    QByteArrayData data[16];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Calculator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Calculator_t qt_meta_stringdata_Calculator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Calculator"
QT_MOC_LITERAL(1, 11, 12), // "digitClicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "digit"
QT_MOC_LITERAL(4, 31, 15), // "operatorClicked"
QT_MOC_LITERAL(5, 47, 2), // "op"
QT_MOC_LITERAL(6, 50, 12), // "equalClicked"
QT_MOC_LITERAL(7, 63, 16), // "backspaceClicked"
QT_MOC_LITERAL(8, 80, 15), // "clearExpression"
QT_MOC_LITERAL(9, 96, 19), // "toggleHistoryWindow"
QT_MOC_LITERAL(10, 116, 13), // "toggleSideBar"
QT_MOC_LITERAL(11, 130, 16), // "handleModeChange"
QT_MOC_LITERAL(12, 147, 4), // "mode"
QT_MOC_LITERAL(13, 152, 12), // "handleSquare"
QT_MOC_LITERAL(14, 165, 10), // "handleSqrt"
QT_MOC_LITERAL(15, 176, 9) // "handleAbs"

    },
    "Calculator\0digitClicked\0\0digit\0"
    "operatorClicked\0op\0equalClicked\0"
    "backspaceClicked\0clearExpression\0"
    "toggleHistoryWindow\0toggleSideBar\0"
    "handleModeChange\0mode\0handleSquare\0"
    "handleSqrt\0handleAbs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Calculator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    1,   72,    2, 0x08 /* Private */,
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    1,   80,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Calculator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Calculator *_t = static_cast<Calculator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->digitClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->operatorClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->equalClicked(); break;
        case 3: _t->backspaceClicked(); break;
        case 4: _t->clearExpression(); break;
        case 5: _t->toggleHistoryWindow(); break;
        case 6: _t->toggleSideBar(); break;
        case 7: _t->handleModeChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->handleSquare(); break;
        case 9: _t->handleSqrt(); break;
        case 10: _t->handleAbs(); break;
        default: ;
        }
    }
}

const QMetaObject Calculator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Calculator.data,
      qt_meta_data_Calculator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Calculator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Calculator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Calculator.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Calculator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
