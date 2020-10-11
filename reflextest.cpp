#include "reflextest.h"
#include "ui_reflextest.h"
#include <QString>
#include <QRandomGenerator>
#include <QTime>
#include <QColor>
#include <QMessageBox>

QString ReflexTest::randomColor() {
    if ( availableColors.size() == 0 ) {
        availableColors = { "Red", "Green", "Blue", "Yellow" };
    }
    int index = QRandomGenerator::global()->generate() % availableColors.size();
    QString color = "background-color: " + availableColors[ index ];
    availableColors.remove(index);
    return color;
}

void ReflexTest::reColorPlayGround() {
    for (int i = 0; i < 16; ++i ) {
        playGround[i]->setStyleSheet( randomColor() );
    }
}

ReflexTest::ReflexTest( QWidget *parent ) : QMainWindow( parent ), ui( new Ui::ReflexTest ) {
    ui->setupUi( this );

    playGround.push_back( ui->colorButton1 );
    playGround.push_back( ui->colorButton2 );
    playGround.push_back( ui->colorButton3 );
    playGround.push_back( ui->colorButton4 );
    playGround.push_back( ui->colorButton5 );
    playGround.push_back( ui->colorButton6 );
    playGround.push_back( ui->colorButton7 );
    playGround.push_back( ui->colorButton8 );
    playGround.push_back( ui->colorButton9 );
    playGround.push_back( ui->colorButton10 );
    playGround.push_back( ui->colorButton11 );
    playGround.push_back( ui->colorButton12 );
    playGround.push_back( ui->colorButton13 );
    playGround.push_back( ui->colorButton14 );
    playGround.push_back( ui->colorButton15 );
    playGround.push_back( ui->colorButton16 );

    for ( int i = 0; i < 16; ++i ) {
        connect( playGround[i], SIGNAL( clicked() ), this, SLOT( on_colorButton_clicked() ) );
    }

    connect( ui->pauseButton, SIGNAL( clicked() ), this, SLOT(on_pauseButton_clicked() ) );
    connect( ui->newGameButton, SIGNAL( clicked() ), this, SLOT( on_startNewGameButton_clicked() ) );

    connect( &timer, SIGNAL( timeout() ), this, SLOT( on_timer_timeout() ) );

    startNewGame();
}

void ReflexTest::startNewGame() {
    timer.start( 2000 );
    reColorPlayGround();
    ui->referenceColorButton->setStyleSheet( randomColor() );
    availableColors = { "Red", "Green", "Blue", "Yellow" };

    badAnswers = 0;
    goodAnswers = 0;
    ui->pointsLabel->setText( QString::number( goodAnswers ) + " good answers / " + QString::number( badAnswers ) + " bad answers." );
}

void ReflexTest::on_startNewGameButton_clicked() {
    startNewGame();
}

void ReflexTest::on_pauseButton_clicked() {
    timer.stop();
    QMessageBox *pauseDialog = new QMessageBox();
    pauseDialog->setText( "You've paused the game. Press \"Continue\" to continue." );
    pauseDialog->addButton( "Continue", QMessageBox::AcceptRole );
    pauseDialog->exec();
    timer.start( 2000 );
}

void ReflexTest::on_colorButton_clicked() {
    QPushButton *sender = qobject_cast<QPushButton *>( QObject::sender() );
    QColor senderColor = sender->palette().color( QPalette::Button );
    QColor refColor = ui->referenceColorButton->palette().color( QPalette::Button );
    if( senderColor == refColor ) {
        ++goodAnswers;
        ui->referenceColorButton->setStyleSheet( randomColor() );
        availableColors = { "Red", "Green", "Blue", "Yellow" };
        nextTest();
    }
    else {
        nextTest();
    }
}

void ReflexTest::nextTest() {
    ui->pointsLabel->setText( QString::number( goodAnswers ) + " good answers / " + QString::number( badAnswers ) + " bad answers." );
    reColorPlayGround();
    timer.start( 2000 );
}

void ReflexTest::on_timer_timeout() {
    ++badAnswers;
    nextTest();
}

ReflexTest::~ReflexTest() {
    delete ui;
}
