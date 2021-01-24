// Sample1-1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#pragma comment( lib, "winmm.lib")
#define SRATE 44100     // サンプリングレート44.1kHz
#define PI 3.14159286   // π
int main()
{
    // wave関係変数
    static HWAVEOUT hWave;
    static WAVEHDR whdr;
    WAVEFORMATEX wfe;
    static char* bWave;
    unsigned int count = 0;
    float b_time = 1.0;                 // 鳴らす時間（秒）の設定
    float f0 = 440.0;                   // ラ（A4）440Hz
    float amplitude = 40.0;             // 振幅
    int data_len = (int)SRATE * b_time; // データの長さ
    bWave = (char *)malloc(data_len);    //波形データのメモリ確保

    // 1秒分のデータを配列に設定する
    for (count = 0; count < data_len; count++) {
        bWave[count] = (char)(amplitude * sin(2 * PI * f0 * count / SRATE));
    }

    wfe.wFormatTag = WAVE_FORMAT_PCM;
    wfe.nChannels = 1;
    wfe.nSamplesPerSec = SRATE;
    wfe.nAvgBytesPerSec = SRATE;
    wfe.wBitsPerSample = 8;
    wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;

    // デバイスのオープン
    waveOutOpen(&hWave, WAVE_MAPPER, &wfe, 0, 0, CALLBACK_NULL);

    whdr.lpData = bWave;
    whdr.dwBufferLength = data_len;
    whdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
    whdr.dwLoops = 1;

    // ヘッダーの準備
    waveOutPrepareHeader(hWave, &whdr, sizeof(WAVEHDR));

    // 波形データの書き出し（再生）
    waveOutWrite(hWave, &whdr, sizeof(WAVEHDR));

    printf("press anny key !");
    getchar();
    return 0;


}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
