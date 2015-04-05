#ifndef AUDIOEFFECTWINDOW_H
#define AUDIOEFFECTWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "bass.h"
#include "bass_fx.h"

namespace Ui {
class AudioEffectWindow;
}

class AudioEffectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AudioEffectWindow(QWidget *parent = 0);
    ~AudioEffectWindow();
public slots:
    void slotCloseWindow();
private slots:
    void slotChorusActiv(bool status);
    void slotChorusSetExample(int index);
    void slotChorusDryMix(int value);
    void slotChorusWetMix(int value);
    void slotChorusfFeedback(int value);
    void slotChorusMinSweep(int value);
    void slotChorusMaxSweep(int value);
    void slotChorusRate(int value);

    void slotReverbActiv(bool status);
    void slotReverbSetExample(int index);
    void slotReverbDryMix(int v);
    void slotReverbWetMix(int v);
    void slotReverbRoomSize(int v);
    void slotReverbDamp(int v);
    void slotReverbWidth(int v);
    void slotReverbMode(int v);

    void slotDistrotionActiv(bool status);
    void slotDistortionSetExample(int index);
    void slotDistrotionDrive(int v);
    void slotDistrotionDryMix(int v);
    void slotDistrotionWetMix(int v);
    void slotDistrotionFreedback(int v);
    void slotDistrotionVolume(int v);

    void slotPhaserActiv(bool status);
    void slotPhaserSetExample(int index);
    void slotPhaserDryMix(int v);
    void slotPhaserWetMix(int v);
    void slotPhaserFeedback(int v);
    void slotPhaserRate(int v);
    void slotPhaserRange(int v);
    void slotPhaserFreq(int v);

    void slotAutowahActov(bool status);
    void slotAutowahSetExample(int index);
    void slotAutowahDryMix(int v);
    void slotAutowahWetMix(int v);
    void slotAutowahFeedBack(int v);
    void slotAutowahRate(int v);
    void slotAutowahRange(int v);
    void slotAutowahFreq(int v);

    void slotDampActiv(bool status);
    void slotDampTarget(int v);
    void slotDampQuit(int v);
    void slotDampRate(int v);
    void slotDampGain(int v);
    void slotDampDelay(int v);

    void slotPitchActiv(bool status);
    void slotfPitchShift(int v);
    void slotPitchSemitones(int v);
    void slotPitchFFTsize(int v);
    void slotPitchOsamp(int v);

    void slotEcho4Activ(bool status);
    void slotEcho4SetExamle(int index);
    void slotEcho4DryMix(int v);
    void slotEcho4WetMix(int v);
    void slotEcho4Feedback(int v);
    void slotEcho4Delay(int v);
    void slotEcho4Stereo(int v);

    void slotEq80(int v);
    void slotEq170(int v);
    void slotEq310(int v);
    void slotEq600(int v);
    void slotEq1000(int v);
    void slotEq3000(int v);
    void slotEq6000(int v);
    void slotEq10000(int v);
    void slotEq12000(int v);
    void slotEq14000(int v);
    void slotEqSendSignalChange();

signals:
    void signalRemoveEffect(int indexEffect);
    void signalChangeSlider(BASS_BFX_CHORUS);
    void signalChangeSlider(BASS_BFX_FREEVERB);
    void signalChangeSlider(BASS_BFX_DISTORTION);
    void signalChangeSlider(BASS_BFX_PHASER);
    void signalChangeSlider(BASS_BFX_AUTOWAH);
    void signalChangeSlider(BASS_BFX_DAMP);
    void signalChangeSlider(BASS_BFX_PITCHSHIFT);
    void signalChangeSlider(BASS_BFX_ECHO4);
    void signalChangeEq(int indexSlider, BASS_DX8_PARAMEQ parameq);

private:
    Ui::AudioEffectWindow *ui;
   enum IndexEffect{CHORUSINDEX,  FREVERBINDEX,  DISTORTIONINDEX, PHASERINDEX, AUTOWAHINDEX, DAMPINDEX, PITCHINDEX, ECHO4INDEX,
                              EQ80INDEX, EQ170INDEX, EQ310INDEX, EQ600INDEX, EQ1000INDEX, EQ3000INDEX, EQ6000INDEX, EQ10000INDEX, EQ12000INDEX, EQ14000INDEX};
   BASS_BFX_CHORUS _chorus;
   BASS_BFX_FREEVERB _reverb;
   BASS_BFX_DISTORTION _distortion;
   BASS_BFX_PHASER _phaser;
   BASS_BFX_AUTOWAH _autowah;
   BASS_BFX_DAMP _damp;
   BASS_BFX_PITCHSHIFT _pitch;
   BASS_BFX_ECHO4 _echo4;
   BASS_DX8_PARAMEQ _eq;
   float _fEqfBandwidth;
};

#endif // AUDIOEFFECTWINDOW_H
