#include "audioeffectwindow.h"
#include "ui_audioeffectwindow.h"

AudioEffectWindow::AudioEffectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AudioEffectWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(ui->pushButtonCloseWindow, SIGNAL(clicked()), SLOT(slotCloseWindow()));

    //Хорус
    _chorus.fDryMix = _chorus.fFeedback = _chorus.fMaxSweep = _chorus.fMinSweep = _chorus.fRate = _chorus.fWetMix = 0;
    _chorus.lChannel = 1 | 2;
    ui->verticalSliderChoorusfDryMix->setRange(-2000, 2000);
    ui->verticalSliderChorusfWetMix->setRange(-2000, 2000);
    ui->verticalSliderChorusfFeedback->setRange(-1000, 1000);
    ui->verticalSliderChorusfMaxSweep->setRange(0, 6000);
    ui->verticalSliderChorusfMinSweep->setRange(0, 6000);
    ui->verticalSliderChorusfRate->setRange(0, 1000);
    ui->comboBoxChorus->addItem("Flanger");
    ui->comboBoxChorus->addItem("Exaggerated");
    ui->comboBoxChorus->addItem("Motocycle");
    ui->comboBoxChorus->addItem("Devil");
    ui->comboBoxChorus->addItem("Who");
    ui->comboBoxChorus->addItem("Back chipmunk");
    ui->comboBoxChorus->addItem("Water");
    ui->comboBoxChorus->addItem("This is the airplane");
    connect(ui->checkBoxChorusActiv, SIGNAL(toggled(bool)), SLOT(slotChorusActiv(bool)));
    connect(ui->comboBoxChorus, SIGNAL(currentIndexChanged(int)), SLOT(slotChorusSetExample(int)));
    slotChorusActiv(false);
    connect(ui->verticalSliderChoorusfDryMix, SIGNAL(sliderMoved(int)), SLOT(slotChorusDryMix(int)));
    connect(ui->verticalSliderChorusfFeedback, SIGNAL(sliderMoved(int)), SLOT(slotChorusfFeedback(int)));
    connect(ui->verticalSliderChorusfMaxSweep, SIGNAL(sliderMoved(int)), SLOT(slotChorusMaxSweep(int)));
    connect(ui->verticalSliderChorusfMinSweep, SIGNAL(sliderMoved(int)), SLOT(slotChorusMinSweep(int)));
    connect(ui->verticalSliderChorusfRate, SIGNAL(sliderMoved(int)), SLOT(slotChorusRate(int)));
    connect(ui->verticalSliderChorusfWetMix, SIGNAL(sliderMoved(int)), SLOT(slotChorusWetMix(int)));

    //Реверберация
    _reverb.fDamp = _reverb.fDryMix = _reverb.fRoomSize = _reverb.fWetMix = _reverb.fWidth = _reverb.lMode = 0;
    _reverb.lChannel = 1 | 2;
    ui->verticalSliderReverbfDryMix->setRange(0, 1000);
    ui->verticalSliderReverbfWetMix->setRange(0, 3000);
    ui->verticalSliderReverbRoomSize->setRange(0, 1000);
    ui->verticalSliderReverbDamp->setRange(0, 1000);
    ui->verticalSliderReverbWidth->setRange(0, 1000);
    ui->verticalSliderRevebMode->setRange(1, 2);
    connect(ui->checkBoxReverbActiv, SIGNAL(toggled(bool)), SLOT(slotReverbActiv(bool)));
    slotReverbActiv(false);
    connect(ui->verticalSliderRevebMode, SIGNAL(sliderMoved(int)), SLOT(slotReverbMode(int)));
    connect(ui->verticalSliderReverbDamp, SIGNAL(sliderMoved(int)), SLOT(slotReverbDamp(int)));
    connect(ui->verticalSliderReverbfDryMix, SIGNAL(sliderMoved(int)), SLOT(slotReverbDryMix(int)));
    connect(ui->verticalSliderReverbfWetMix, SIGNAL(sliderMoved(int)), SLOT(slotReverbWetMix(int)));
    connect(ui->verticalSliderReverbRoomSize, SIGNAL(sliderMoved(int)), SLOT(slotReverbRoomSize(int)));
    connect(ui->verticalSliderReverbWidth, SIGNAL(sliderMoved(int)), SLOT(slotReverbWidth(int)));

    //Дисторшн
    _distortion.fDrive = _distortion.fDryMix = _distortion.fFeedback = _distortion.fVolume = _distortion.fWetMix = 0;
    _distortion.lChannel = 1 | 2;
    ui->verticalSliderDistortionDrive->setRange(0, 500);
    ui->verticalSliderDistortionDryMix->setRange(-500, 500);
    ui->verticalSliderDistortionWetMix->setRange(-500, 500);
    ui->verticalSliderDistortionFreedback->setRange(-100, 100);
    ui->verticalSliderDistortionVolume->setRange(0, 200);
    ui->comboBoxDistortion->addItem("Hard");
    ui->comboBoxDistortion->addItem("VeryHard");
    ui->comboBoxDistortion->addItem("Medium");
    ui->comboBoxDistortion->addItem("Soft");
    connect(ui->checkBoxDistortionActiv, SIGNAL(toggled(bool)), SLOT(slotDistrotionActiv(bool)));
    connect(ui->comboBoxDistortion, SIGNAL(currentIndexChanged(int)), SLOT(slotDistortionSetExample(int)));
    slotDistrotionActiv(false);
    connect(ui->verticalSliderDistortionDrive, SIGNAL(sliderMoved(int)), SLOT(slotDistrotionDrive(int)));
    connect(ui->verticalSliderDistortionDryMix, SIGNAL(sliderMoved(int)), SLOT(slotDistrotionDryMix(int)));
    connect(ui->verticalSliderDistortionFreedback, SIGNAL(sliderMoved(int)), SLOT(slotDistrotionFreedback(int)));
    connect(ui->verticalSliderDistortionVolume, SIGNAL(sliderMoved(int)), SLOT(slotDistrotionVolume(int)));
    connect(ui->verticalSliderDistortionWetMix, SIGNAL(sliderMoved(int)), SLOT(slotDistrotionWetMix(int)));

    //Фазер
    _phaser.fDryMix = _phaser.fFeedback = _phaser.fFreq = _phaser.fRange = _phaser.fRate = _phaser.fWetMix = 0;
    _phaser.lChannel = 1 | 2;
    ui->verticalSliderPhaserDryMix->setRange(-200, 200);
    ui->verticalSliderPhaserFeedback->setRange(-100, 100);
    ui->verticalSliderPhaserFreq->setRange(0, 1000);
    ui->verticalSliderPhaserRange->setRange(0, 100);
    ui->verticalSliderPhaserRate->setRange(0, 100);
    ui->verticalSliderPhaserWetMix->setRange(-200, 200);
    ui->comboBoxPhaser->addItem("Phase shift");
    ui->comboBoxPhaser->addItem("Slow invert");
    ui->comboBoxPhaser->addItem("Basic phase");
    ui->comboBoxPhaser->addItem("Phase w/ FB");
    ui->comboBoxPhaser->addItem("Med. phase");
    ui->comboBoxPhaser->addItem("Fast phase");
    ui->comboBoxPhaser->addItem("Invert w/FB");
    ui->comboBoxPhaser->addItem("Tremolo Wah");
    connect(ui->checkBoxPhaserActiv, SIGNAL(toggled(bool)), SLOT(slotPhaserActiv(bool)));
    connect(ui->comboBoxPhaser, SIGNAL(currentIndexChanged(int)), SLOT(slotPhaserSetExample(int)));
    slotPhaserActiv(false);
    connect(ui->verticalSliderPhaserDryMix, SIGNAL(sliderMoved(int)), SLOT(slotPhaserDryMix(int)));
    connect(ui->verticalSliderPhaserFeedback, SIGNAL(sliderMoved(int)), SLOT(slotPhaserFeedback(int)));
    connect(ui->verticalSliderPhaserFreq, SIGNAL(sliderMoved(int)), SLOT(slotPhaserFreq(int)));
    connect(ui->verticalSliderPhaserRange, SIGNAL(sliderMoved(int)), SLOT(slotPhaserRange(int)));
    connect(ui->verticalSliderPhaserRate, SIGNAL(sliderMoved(int)), SLOT(slotPhaserRate(int)));
    connect(ui->verticalSliderPhaserWetMix, SIGNAL(sliderMoved(int)), SLOT(slotPhaserWetMix(int)));

    //Вау- эффет
    _autowah.fDryMix = _autowah.fFeedback = _autowah.fFreq = _autowah.fRange = _autowah.fRate = _autowah.fWetMix = 0;
    _autowah.lChannel = 1 | 2;
    ui->verticalSliderAutowahDryMix->setRange(-200, 200);
    ui->verticalSliderAutowahWetMix->setRange(-200, 200);
    ui->verticalSliderAutowahFeedBack->setRange(-100, 100);
    ui->verticalSliderAutowahRate->setRange(0, 100);
    ui->verticalSliderAutowahRange->setRange(0, 100);
    ui->verticalSliderAutowahFreq->setRange(0, 1000);
    ui->comboBoxAutowah->addItem("Slow");
    ui->comboBoxAutowah->addItem("Fast");
    ui->comboBoxAutowah->addItem("Hi Fast");
    connect(ui->checkBoxAutowahActiv, SIGNAL(toggled(bool)), SLOT(slotAutowahActov(bool)));
    connect(ui->comboBoxAutowah, SIGNAL(currentIndexChanged(int)), SLOT(slotAutowahSetExample(int)));
    slotAutowahActov(false);
    connect(ui->verticalSliderAutowahDryMix, SIGNAL(sliderMoved(int)), SLOT(slotAutowahDryMix(int)));
    connect(ui->verticalSliderAutowahFeedBack, SIGNAL(sliderMoved(int)), SLOT(slotAutowahFeedBack(int)));
    connect(ui->verticalSliderAutowahFreq, SIGNAL(sliderMoved(int)), SLOT(slotAutowahFreq(int)));
    connect(ui->verticalSliderAutowahRange, SIGNAL(sliderMoved(int)), SLOT(slotAutowahRange(int)));
    connect(ui->verticalSliderAutowahRate, SIGNAL(sliderMoved(int)), SLOT(slotAutowahRate(int)));
    connect(ui->verticalSliderAutowahWetMix, SIGNAL(sliderMoved(int)), SLOT(slotAutowahWetMix(int)));

    //Затухание
    _damp.fTarget = _damp.fQuiet = _damp.fRate = _damp.fGain = _damp.fDelay = 0;
    _damp.lChannel = 1 | 2;
    ui->verticalSliderDampTarget->setRange(0, 100);
    ui->verticalSliderDampQuit->setRange(0, 100);
    ui->verticalSliderDampRate->setRange(0, 100);
    ui->verticalSliderDampGain->setRange(0, 10000);
    ui->verticalSliderDampDelay->setRange(0, 10000);
    connect(ui->checkBoxDampActiv, SIGNAL(toggled(bool)), SLOT(slotDampActiv(bool)));
    slotDampActiv(false);
    connect(ui->verticalSliderDampDelay, SIGNAL(sliderMoved(int)), SLOT(slotDampDelay(int)));
    connect(ui->verticalSliderDampGain, SIGNAL(sliderMoved(int)), SLOT(slotDampGain(int)));
    connect(ui->verticalSliderDampQuit, SIGNAL(sliderMoved(int)), SLOT(slotDampQuit(int)));
    connect(ui->verticalSliderDampRate, SIGNAL(sliderMoved(int)), SLOT(slotDampRate(int)));
    connect(ui->verticalSliderDampTarget, SIGNAL(sliderMoved(int)), SLOT(slotDampTarget(int)));

    //Питч
    _pitch.fPitchShift = 1.0f; _pitch.fSemitones  = 0; _pitch.lFFTsize = 2048; _pitch.lOsamp = 8; _pitch.lChannel = 1 | 2;
    ui->verticalSliderPitchShift->setRange(50, 200);
    ui->verticalSliderPitchSemitones->setRange(0, 1000);
    ui->verticalSliderPitchFFTsize->setRange(1, 8);
    ui->verticalSliderPitchOsamp->setRange(1, 8);
    connect(ui->checkBoxPitchActiv, SIGNAL(toggled(bool)), SLOT(slotPitchActiv(bool)));
    slotPitchActiv(false);
    connect(ui->verticalSliderPitchFFTsize, SIGNAL(sliderMoved(int)), SLOT(slotPitchFFTsize(int)));
    connect(ui->verticalSliderPitchOsamp, SIGNAL(sliderMoved(int)), SLOT(slotPitchOsamp(int)));
    connect(ui->verticalSliderPitchSemitones, SIGNAL(sliderMoved(int)), SLOT(slotPitchSemitones(int)));
    connect(ui->verticalSliderPitchShift, SIGNAL(sliderMoved(int)), SLOT(slotfPitchShift(int)));

    //Эхо
    _echo4.fDryMix = _echo4.fWetMix = _echo4.fFeedback = _echo4.fDelay = 0; _echo4.bStereo = true; _echo4.lChannel = 1 | 2;
    ui->verticalSliderEchoDryMix->setRange(-200, 200);
    ui->verticalSliderEchoWetMix->setRange(-200, 200);
    ui->verticalSliderEchoFeedBack->setRange(-100, 100);
    ui->verticalSliderEchoDelay->setRange(0, 100);
    ui->verticalSliderEchoStereo->setRange(0, 1);
    ui->comboBoxEcho->addItem("Small Echo");
    ui->comboBoxEcho->addItem("Many Echoes");
    ui->comboBoxEcho->addItem("Reverse Echoes");
    ui->comboBoxEcho->addItem("Robotic Voice");
    connect(ui->checkBoxEchoActiv, SIGNAL(toggled(bool)), SLOT(slotEcho4Activ(bool)));
    connect(ui->comboBoxEcho, SIGNAL(currentIndexChanged(int)), SLOT(slotEcho4SetExamle(int)));
    slotEcho4Activ(false);
    connect(ui->verticalSliderEchoDelay, SIGNAL(sliderMoved(int)), SLOT(slotEcho4Delay(int)));
    connect(ui->verticalSliderEchoDryMix, SIGNAL(sliderMoved(int)), SLOT(slotEcho4DryMix(int)));
    connect(ui->verticalSliderEchoFeedBack, SIGNAL(sliderMoved(int)), SLOT(slotEcho4Feedback(int)));
    connect(ui->verticalSliderEchoStereo, SIGNAL(sliderMoved(int)), SLOT(slotEcho4Stereo(int)));
    connect(ui->verticalSliderEchoWetMix, SIGNAL(sliderMoved(int)), SLOT(slotEcho4WetMix(int)));

    //Экволайзер
    _fEqfBandwidth = 4.9f;
   ui->verticalSliderEq80->setRange(-15, 15);
   ui->verticalSliderEq80->setValue(0);
   ui->verticalSliderEq170->setRange(-15, 15);
   ui->verticalSliderEq170->setValue(0);
   ui->verticalSliderEq310->setRange(-15, 15);
   ui->verticalSliderEq310->setValue(0);
   ui->verticalSliderEq600->setRange(-15, 15);
   ui->verticalSliderEq600->setValue(0);
   ui->verticalSliderEq1000->setRange(-15, 15);
   ui->verticalSliderEq1000->setValue(0);
   ui->verticalSliderEq3000->setRange(-15, 15);
   ui->verticalSliderEq3000->setValue(0);
   ui->verticalSliderEq6000->setRange(-15, 15);
   ui->verticalSliderEq6000->setValue(0);
   ui->verticalSliderEq10000->setRange(-15, 15);
   ui->verticalSliderEq10000->setValue(0);
   ui->verticalSliderEq12000->setRange(-15, 15);
   ui->verticalSliderEq12000->setValue(0);
   ui->verticalSliderEq14000->setRange(-15, 15);
   ui->verticalSliderEq14000->setValue(0);
    connect(ui->verticalSliderEq80, SIGNAL(sliderMoved(int)), SLOT(slotEq80(int)));
    connect(ui->verticalSliderEq170, SIGNAL(sliderMoved(int)), SLOT(slotEq170(int)));
    connect(ui->verticalSliderEq310, SIGNAL(sliderMoved(int)), SLOT(slotEq310(int)));
    connect(ui->verticalSliderEq600, SIGNAL(sliderMoved(int)), SLOT(slotEq600(int)));
    connect(ui->verticalSliderEq1000, SIGNAL(sliderMoved(int)), SLOT(slotEq1000(int)));
    connect(ui->verticalSliderEq3000, SIGNAL(sliderMoved(int)), SLOT(slotEq3000(int)));
    connect(ui->verticalSliderEq6000, SIGNAL(sliderMoved(int)), SLOT(slotEq6000(int)));
    connect(ui->verticalSliderEq10000, SIGNAL(sliderMoved(int)), SLOT(slotEq10000(int)));
    connect(ui->verticalSliderEq12000, SIGNAL(sliderMoved(int)), SLOT(slotEq12000(int)));
    connect(ui->verticalSliderEq14000, SIGNAL(sliderMoved(int)), SLOT(slotEq14000(int)));

}

AudioEffectWindow::~AudioEffectWindow()
{
    delete ui;
}

void AudioEffectWindow::slotCloseWindow()
{
    close();
}

void AudioEffectWindow::slotChorusActiv(bool status)
{
    if(!status)
    {
        emit signalRemoveEffect(CHORUSINDEX);
        ui->groupBoxChorus->setDisabled(true);
        ui->comboBoxChorus->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_chorus);
        ui->groupBoxChorus->setEnabled(true);
        ui->comboBoxChorus->setEnabled(true);
    }
}

void AudioEffectWindow::slotChorusSetExample(int index)
{
    int CHANNEL = 1 | 2;
    switch (index) {
    case 0:
        _chorus.fDryMix = 1.0f;  _chorus.fWetMix = 0.35f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 5.0f; _chorus.fRate = 1.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 1:
        _chorus.fDryMix = 0.7f;  _chorus.fWetMix = 0.25f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 200.0f; _chorus.fRate = 50.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 2:
        _chorus.fDryMix = 0.9f;  _chorus.fWetMix = 0.45f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 100.0f; _chorus.fRate = 25.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 3:
        _chorus.fDryMix = 0.9f;  _chorus.fWetMix = 0.35f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 50.0f; _chorus.fRate = 200.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 4:
        _chorus.fDryMix = 0.9f;  _chorus.fWetMix = 0.35f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 400.0f; _chorus.fRate = 200.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 5:
        _chorus.fDryMix = 0.9f;  _chorus.fWetMix = -0.2f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 400.0f; _chorus.fRate = 400.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    case 6:
        _chorus.fDryMix = 0.9f;  _chorus.fWetMix = -0.4f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 2.0f; _chorus.fRate = 1.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
    case 7:
        _chorus.fDryMix = 0.3f;  _chorus.fWetMix = 0.4f; _chorus.fFeedback = 0.5f; _chorus.fMinSweep = 1.0f;
        _chorus.fMaxSweep = 10.0f; _chorus.fRate = 5.0f; _chorus.lChannel = CHANNEL;
        emit signalChangeSlider(_chorus);
        break;
    }
}

//----------------------------------------------------------------------
//Хорус
void AudioEffectWindow::slotChorusDryMix(int value)
{
    _chorus.fDryMix = (float) value / 1000.0f;
    emit signalChangeSlider(_chorus);
}

void AudioEffectWindow::slotChorusWetMix(int value)
{
    _chorus.fWetMix = (float) value / 1000.0f;
    emit signalChangeSlider(_chorus);
}

void AudioEffectWindow::slotChorusfFeedback(int value)
{
    _chorus.fFeedback = (float) value / 1000.0f;
    emit signalChangeSlider(_chorus);
}

void AudioEffectWindow::slotChorusMinSweep(int value)
{
    _chorus.fMinSweep = (float) value;
    emit signalChangeSlider(_chorus);
}

void AudioEffectWindow::slotChorusMaxSweep(int value)
{
    _chorus.fMaxSweep = (float)  value;
    emit signalChangeSlider(_chorus);
}

void AudioEffectWindow::slotChorusRate(int value)
{
    _chorus.fRate = (float) value;
    emit signalChangeSlider(_chorus);
}


//----------------------------------------------------------------------
//Ревербирация
void AudioEffectWindow::slotReverbActiv(bool status)
{
    if(!status)
    {
        emit signalRemoveEffect(FREVERBINDEX);
        ui->groupBoxFReverb->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_reverb);
        ui->groupBoxFReverb->setEnabled(true);
    }
}

void AudioEffectWindow::slotReverbSetExample(int index)
{

}

void AudioEffectWindow::slotReverbDryMix(int v)
{
    _reverb.fDryMix = (float) v / 1000.0f;
    emit signalChangeSlider(_reverb);
}

void AudioEffectWindow::slotReverbWetMix(int v)
{
    _reverb.fWetMix = (float) v / 1000.0f;
     emit signalChangeSlider(_reverb);
}

void AudioEffectWindow::slotReverbRoomSize(int v)
{
    _reverb.fRoomSize = (float) v / 1000.0f;
     emit signalChangeSlider(_reverb);
}

void AudioEffectWindow::slotReverbDamp(int v)
{
    _reverb.fDamp = (float) v / 1000.0f;
     emit signalChangeSlider(_reverb);
}

void AudioEffectWindow::slotReverbWidth(int v)
{
    _reverb.fWidth = (float) v / 1000.0f;
     emit signalChangeSlider(_reverb);
}

void AudioEffectWindow::slotReverbMode(int v)
{
    _reverb.lMode = v;
    emit signalChangeSlider(_reverb);
}

//----------------------------------------------------------------------
//Дисторшн
void AudioEffectWindow::slotDistrotionActiv(bool status)
{
    if(!status)
    {
        emit signalRemoveEffect(DISTORTIONINDEX);
        ui->groupBoxDistortion->setDisabled(true);
        ui->comboBoxDistortion->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_distortion);
        ui->groupBoxDistortion->setEnabled(true);
        ui->comboBoxDistortion->setEnabled(true);
    }
}

void AudioEffectWindow::slotDistortionSetExample(int index)
{
    int CHANNEL = 1 | 2;
    switch (index) {
    case 0:
        _distortion.fDrive = 1.0f ; _distortion.fDryMix = 0.0f; _distortion.fWetMix = 1.0f;
        _distortion.fFeedback = 0.0f; _distortion.fVolume = 1.0f; _distortion.lChannel = CHANNEL;
        emit signalChangeSlider(_distortion);
        break;
    case 1:
        _distortion.fDrive = 5.0f ; _distortion.fDryMix = 0.0f; _distortion.fWetMix = 1.0f;
        _distortion.fFeedback = 0.1f; _distortion.fVolume = 1.0f; _distortion.lChannel = CHANNEL;
        emit signalChangeSlider(_distortion);
        break;
    case 2:
        _distortion.fDrive = 0.2f ; _distortion.fDryMix = 1.0f; _distortion.fWetMix = 1.0f;
        _distortion.fFeedback = 0.1f; _distortion.fVolume = 1.0f; _distortion.lChannel = CHANNEL;
        emit signalChangeSlider(_distortion);
        break;
    case 3:
        _distortion.fDrive = 0.0f ; _distortion.fDryMix = -2.95f; _distortion.fWetMix = -0.05f;
        _distortion.fFeedback = -0.18f; _distortion.fVolume = 0.25f; _distortion.lChannel = CHANNEL;
        emit signalChangeSlider(_distortion);
        break;
    }
}

void AudioEffectWindow::slotDistrotionDrive(int v)
{
    _distortion.fDrive = (float) v / 100.0f;
    emit signalChangeSlider(_distortion);
}

void AudioEffectWindow::slotDistrotionDryMix(int v)
{
    _distortion.fDryMix = (float) v / 100.0f;
    emit signalChangeSlider(_distortion);
}

void AudioEffectWindow::slotDistrotionWetMix(int v)
{
    _distortion.fWetMix = (float) v / 100.0f;
    emit signalChangeSlider(_distortion);
}

void AudioEffectWindow::slotDistrotionFreedback(int v)
{
    _distortion.fFeedback = (float) v / 100.0f;
    emit signalChangeSlider(_distortion);
}

void AudioEffectWindow::slotDistrotionVolume(int v)
{
    _distortion.fVolume = (float) v / 100.0f;
    emit signalChangeSlider(_distortion);
}

//----------------------------------------------------------------------
//Фазер
void AudioEffectWindow::slotPhaserActiv(bool status)
{
    if(!status)
    {
        signalRemoveEffect(PHASERINDEX);
        ui->groupBoxPhaser->setDisabled(true);
        ui->comboBoxPhaser->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_phaser);
        ui->groupBoxPhaser->setEnabled(true);
        ui->comboBoxPhaser->setEnabled(true);
    }
}

void AudioEffectWindow::slotPhaserSetExample(int index)
{
    int CHANNEL = 1 | 2;
    switch (index) {
    case 0:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.0f; _phaser.fRate = 1.0f;
        _phaser.fRange = 4.0f; _phaser.fFreq = 100.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 1:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = -0.999f; _phaser.fFeedback = -0.6f; _phaser.fRate = 0.2f;
        _phaser.fRange = 6.0f; _phaser.fFreq = 100.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 2:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.0f; _phaser.fRate = 1.0f;
        _phaser.fRange = 4.3f; _phaser.fFreq = 50.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 3:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.6f; _phaser.fRate = 1.0f;
        _phaser.fRange = 4.0f; _phaser.fFreq = 40.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 4:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.0f; _phaser.fRate = 1.0f;
        _phaser.fRange = 7.0f; _phaser.fFreq = 100.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 5:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.0f; _phaser.fRate = 1.0f;
        _phaser.fRange = 7.0f; _phaser.fFreq = 400.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 6:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = -0.999f; _phaser.fFeedback = -0.2f; _phaser.fRate = 1.0f;
        _phaser.fRange = 7.0f; _phaser.fFreq = 200.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    case 7:
        _phaser.fDryMix = 0.999f; _phaser.fWetMix = 0.999f; _phaser.fFeedback = 0.6f; _phaser.fRate = 1.0f;
        _phaser.fRange = 4.0f; _phaser.fFreq = 60.0f; _phaser.lChannel = CHANNEL;
        emit signalChangeSlider(_phaser);
        break;
    }
}

void AudioEffectWindow::slotPhaserDryMix(int v)
{
    _phaser.fDryMix = (float) v / 100.0f;
    emit signalChangeSlider(_phaser);
}

void AudioEffectWindow::slotPhaserWetMix(int v)
{
    _phaser.fWetMix = (float) v / 100.0f;
    emit signalChangeSlider(_phaser);
}

void AudioEffectWindow::slotPhaserFeedback(int v)
{
    _phaser.fFeedback = (float) v / 100.0f;
    emit signalChangeSlider(_phaser);
}

void AudioEffectWindow::slotPhaserRate(int v)
{
    _phaser.fRate = (float) v / 10.0f;
    emit signalChangeSlider(_phaser);
}

void AudioEffectWindow::slotPhaserRange(int v)
{
    _phaser.fRange = (float) v / 10.0f;
    emit signalChangeSlider(_phaser);
}

void AudioEffectWindow::slotPhaserFreq(int v)
{
    _phaser.fFreq = (float) v;
    emit signalChangeSlider(_phaser);
}

//----------------------------------------------------------------------
//Ква- эффект
void AudioEffectWindow::slotAutowahActov(bool status)
{
    if(!status)
    {
        signalRemoveEffect(AUTOWAHINDEX);
        ui->groupBoxAutowah->setDisabled(true);
        ui->comboBoxAutowah->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_autowah);
        ui->groupBoxAutowah->setEnabled(true);
        ui->comboBoxAutowah->setEnabled(true);
    }
}

void AudioEffectWindow::slotAutowahSetExample(int index)
{
    int CHANNEL = 1 | 2;
    switch (index) {
    case 0:
        _autowah.fDryMix = 0.500f; _autowah.fWetMix = 1.500f; _autowah.fFeedback = 0.5f; _autowah.fRate = 2.0f;
        _autowah.fRange = 4.3f; _autowah.fFreq = 50.0f; _autowah.lChannel = CHANNEL;
        emit signalChangeSlider(_autowah);
        break;
    case 1:
        _autowah.fDryMix = 0.500f; _autowah.fWetMix = 1.500f; _autowah.fFeedback = 0.5f; _autowah.fRate = 5.0f;
        _autowah.fRange = 5.3f; _autowah.fFreq = 50.0f; _autowah.lChannel = CHANNEL;
        emit signalChangeSlider(_autowah);
        break;
    case 2:
        _autowah.fDryMix = 0.500f; _autowah.fWetMix = 1.500f; _autowah.fFeedback = 0.5f; _autowah.fRate = 5.0f;
        _autowah.fRange = 4.3f; _autowah.fFreq = 500.0f; _autowah.lChannel = CHANNEL;
        emit signalChangeSlider(_autowah);
        break;
    }
}

void AudioEffectWindow::slotAutowahDryMix(int v)
{
    _autowah.fDryMix = (float) v / 100.0f;
    emit signalChangeSlider(_autowah);
}

void AudioEffectWindow::slotAutowahWetMix(int v)
{
    _autowah.fWetMix = (float) v / 100.0f;
    emit signalChangeSlider(_autowah);
}

void AudioEffectWindow::slotAutowahFeedBack(int v)
{
    _autowah.fFeedback = (float) v / 100.0f;
    emit signalChangeSlider(_autowah);
}

void AudioEffectWindow::slotAutowahRate(int v)
{
    _autowah.fRate = (float) v / 100.0f;
    emit signalChangeSlider(_autowah);
}

void AudioEffectWindow::slotAutowahRange(int v)
{
    _autowah.fRange = (float) v / 100.0f;
    emit signalChangeSlider(_autowah);
}

void AudioEffectWindow::slotAutowahFreq(int v)
{
    _autowah.fFreq = (float) v;
    emit signalChangeSlider(_autowah);
}

//----------------------------------------------------------------------
//Затухание
void AudioEffectWindow::slotDampActiv(bool status)
{
    if(!status)
    {
        signalRemoveEffect(DAMPINDEX);
        ui->groupBoxDamp->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_damp);
        ui->groupBoxDamp->setEnabled(true);
    }
}

void AudioEffectWindow::slotDampTarget(int v)
{
    _damp.fTarget = (float) v / 100.0f;
     emit signalChangeSlider(_damp);
}

void AudioEffectWindow::slotDampQuit(int v)
{
    _damp.fQuiet = (float) v / 100.0f;
    emit signalChangeSlider(_damp);
}

void AudioEffectWindow::slotDampRate(int v)
{
    _damp.fRate = (float) v / 100.0f;
    emit signalChangeSlider(_damp);
}

void AudioEffectWindow::slotDampGain(int v)
{
    _damp.fGain = (float) v / 100.0f;
    emit signalChangeSlider(_damp);
}

void AudioEffectWindow::slotDampDelay(int v)
{
    _damp.fDelay = (float) v / 100.0;
    emit signalChangeSlider(_damp);
}

//Питч
void AudioEffectWindow::slotPitchActiv(bool status)
{
    if(!status)
    {
        signalRemoveEffect(PITCHINDEX);
        ui->groupBoxPitch->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_pitch);
        ui->groupBoxPitch->setEnabled(true);
    }
}

void AudioEffectWindow::slotfPitchShift(int v)
{
    _pitch.fPitchShift = (float) v / 100.0f;
    emit signalChangeSlider(_pitch);
}

void AudioEffectWindow::slotPitchSemitones(int v)
{
    _pitch.fSemitones = (float) v / 100.0f;
    emit signalChangeSlider(_pitch);
}

void AudioEffectWindow::slotPitchFFTsize(int v)
{
    _pitch.lFFTsize = v * 1024;
    emit signalChangeSlider(_pitch);
}

void AudioEffectWindow::slotPitchOsamp(int v)
{
    _pitch.lOsamp = v * 4;
    emit signalChangeSlider(_pitch);
}

//Эхо 4
void AudioEffectWindow::slotEcho4Activ(bool status)
{
    if(!status)
    {
        signalRemoveEffect(ECHO4INDEX);
        ui->groupBoxEcho->setDisabled(true);
        ui->comboBoxEcho->setDisabled(true);
    }
    else
    {
        emit signalChangeSlider(_echo4);
        ui->groupBoxEcho->setEnabled(true);
        ui->comboBoxEcho->setEnabled(true);
    }
}

void AudioEffectWindow::slotEcho4SetExamle(int index)
{
    int CHANNEL = 1 | 2;
    bool STEREO = true;
    switch (index) {
    case 0:
        _echo4.fDryMix = 0.999f; _echo4.fWetMix = 0.999f; _echo4.fFeedback = 0.0f;  _echo4.fDelay = 0.20f; _echo4.bStereo =  STEREO;
        _echo4.lChannel = CHANNEL;
        emit signalChangeSlider(_echo4);
        break;
    case 1:
        _echo4.fDryMix = 0.999f; _echo4.fWetMix = 0.999f; _echo4.fFeedback = 0.7f;  _echo4.fDelay = 0.50f; _echo4.bStereo =  STEREO;
        _echo4.lChannel = CHANNEL;
        emit signalChangeSlider(_echo4);
        break;
    case 2:
        _echo4.fDryMix = 0.999f; _echo4.fWetMix = 0.999f; _echo4.fFeedback = -0.7f;  _echo4.fDelay = 0.80f; _echo4.bStereo =  STEREO;
        _echo4.lChannel = CHANNEL;
        emit signalChangeSlider(_echo4);
        break;
    case 3:
        _echo4.fDryMix = 0.500f; _echo4.fWetMix = 0.800f; _echo4.fFeedback = 0.5f;  _echo4.fDelay = 0.10f; _echo4.bStereo =  STEREO;
        _echo4.lChannel = CHANNEL;
        emit signalChangeSlider(_echo4);
        break;
    }
}

void AudioEffectWindow::slotEcho4DryMix(int v)
{
    _echo4.fDryMix = (float) v / 100.0f;
    emit signalChangeSlider(_echo4);
}

void AudioEffectWindow::slotEcho4WetMix(int v)
{
    _echo4.fWetMix = (float) v / 100.0f;
    emit signalChangeSlider(_echo4);
}

void AudioEffectWindow::slotEcho4Feedback(int v)
{
    _echo4.fFeedback = (float) v / 100.0f;
    emit signalChangeSlider(_echo4);
}

void AudioEffectWindow::slotEcho4Delay(int v)
{
    _echo4.fDelay = (float) v / 100.0f;
    emit signalChangeSlider(_echo4);
}

void AudioEffectWindow::slotEcho4Stereo(int v)
{
    _echo4.bStereo = (bool) v;
    emit signalChangeSlider(_echo4);
}

//Экволайзер
void AudioEffectWindow::slotEq80(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 80.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ80INDEX, eq);
}

void AudioEffectWindow::slotEq170(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 170.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ170INDEX, eq);
}

void AudioEffectWindow::slotEq310(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 310.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ310INDEX, eq);
}

void AudioEffectWindow::slotEq600(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth = _fEqfBandwidth;
    eq.fCenter = 600.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ600INDEX, eq);
}

void AudioEffectWindow::slotEq1000(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 1000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ1000INDEX, eq);
}

void AudioEffectWindow::slotEq3000(int v)
{\
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 3000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ3000INDEX, eq);
}

void AudioEffectWindow::slotEq6000(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 6000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ6000INDEX, eq);
}

void AudioEffectWindow::slotEq10000(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 10000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ10000INDEX, eq);
}

void AudioEffectWindow::slotEq12000(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 12000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ12000INDEX, eq);
}

void AudioEffectWindow::slotEq14000(int v)
{
    BASS_DX8_PARAMEQ eq;
    eq.fBandwidth =  _fEqfBandwidth;
    eq.fCenter = 14000.0f;
    eq.fGain = (float) v;
    emit signalChangeEq(EQ14000INDEX, eq);
}

void AudioEffectWindow::slotEqSendSignalChange()
{
    slotEq80(ui->verticalSliderEq80->value());
    slotEq170(ui->verticalSliderEq170->value());
    slotEq310(ui->verticalSliderEq310->value());
    slotEq600(ui->verticalSliderEq600->value());
    slotEq1000(ui->verticalSliderEq1000->value());
    slotEq3000(ui->verticalSliderEq3000->value());
    slotEq6000(ui->verticalSliderEq6000->value());
    slotEq10000(ui->verticalSliderEq10000->value());
    slotEq12000(ui->verticalSliderEq12000->value());
    slotEq14000(ui->verticalSliderEq14000->value());

}

