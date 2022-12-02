/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../robotTheorique/mainwindow.h"
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
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      29,   11,   11,   11, 0x0a,
      45,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x0a,
      75,   11,   11,   11, 0x0a,
      92,   11,   11,   11, 0x0a,
     108,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     139,   11,   11,   11, 0x0a,
     152,   11,   11,   11, 0x0a,
     167,   11,   11,   11, 0x0a,
     183,   11,   11,   11, 0x0a,
     198,   11,   11,   11, 0x0a,
     221,   11,   11,   11, 0x0a,
     247,   11,   11,   11, 0x0a,
     271,   11,   11,   11, 0x0a,
     287,   11,   11,   11, 0x0a,
     306,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0onStartX_Right()\0"
    "onStartX_Left()\0onStartY_Up()\0"
    "onStartY_Down()\0onStartZ_Right()\0"
    "onStartZ_Left()\0onGoalX_Right()\0"
    "onGoalX_Left()\0onGoalY_Up()\0onGoalY_Down()\0"
    "onGoalZ_Right()\0onGoalZ_Left()\0"
    "on_courbesPressed(int)\0on_vitesseChanged(double)\0"
    "on_rayonChanged(double)\0moveTheorique()\0"
    "on_moveTheorique()\0on_startStop(bool)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->onStartX_Right(); break;
        case 1: _t->onStartX_Left(); break;
        case 2: _t->onStartY_Up(); break;
        case 3: _t->onStartY_Down(); break;
        case 4: _t->onStartZ_Right(); break;
        case 5: _t->onStartZ_Left(); break;
        case 6: _t->onGoalX_Right(); break;
        case 7: _t->onGoalX_Left(); break;
        case 8: _t->onGoalY_Up(); break;
        case 9: _t->onGoalY_Down(); break;
        case 10: _t->onGoalZ_Right(); break;
        case 11: _t->onGoalZ_Left(); break;
        case 12: _t->on_courbesPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_vitesseChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->on_rayonChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->moveTheorique(); break;
        case 16: _t->on_moveTheorique(); break;
        case 17: _t->on_startStop((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
