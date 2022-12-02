/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../courbesDubins/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      21,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      57,   11,   11,   11, 0x0a,
      66,   11,   11,   11, 0x0a,
      82,   11,   11,   11, 0x0a,
     105,   11,   11,   11, 0x0a,
     122,   11,   11,   11, 0x0a,
     138,   11,   11,   11, 0x0a,
     152,   11,   11,   11, 0x0a,
     168,   11,   11,   11, 0x0a,
     185,   11,   11,   11, 0x0a,
     201,   11,   11,   11, 0x0a,
     217,   11,   11,   11, 0x0a,
     232,   11,   11,   11, 0x0a,
     245,   11,   11,   11, 0x0a,
     260,   11,   11,   11, 0x0a,
     276,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_rsr()\0on_rsl()\0on_lsr()\0"
    "on_lsl()\0on_rlr()\0on_lrl()\0on_justCourbe()\0"
    "on_courbesPressed(int)\0onStartX_Right()\0"
    "onStartX_Left()\0onStartY_Up()\0"
    "onStartY_Down()\0onStartZ_Right()\0"
    "onStartZ_Left()\0onGoalX_Right()\0"
    "onGoalX_Left()\0onGoalY_Up()\0onGoalY_Down()\0"
    "onGoalZ_Right()\0onGoalZ_Left()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_rsr(); break;
        case 1: _t->on_rsl(); break;
        case 2: _t->on_lsr(); break;
        case 3: _t->on_lsl(); break;
        case 4: _t->on_rlr(); break;
        case 5: _t->on_lrl(); break;
        case 6: _t->on_justCourbe(); break;
        case 7: _t->on_courbesPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onStartX_Right(); break;
        case 9: _t->onStartX_Left(); break;
        case 10: _t->onStartY_Up(); break;
        case 11: _t->onStartY_Down(); break;
        case 12: _t->onStartZ_Right(); break;
        case 13: _t->onStartZ_Left(); break;
        case 14: _t->onGoalX_Right(); break;
        case 15: _t->onGoalX_Left(); break;
        case 16: _t->onGoalY_Up(); break;
        case 17: _t->onGoalY_Down(); break;
        case 18: _t->onGoalZ_Right(); break;
        case 19: _t->onGoalZ_Left(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
