#include "buzzer.h"

#define BEEP_ON HIGH
#define BEEP_OFF LOW
// #define BEEP_ON LOW
// #define BEEP_OFF HIGH

volatile uint16_t Buzzer::m_count = 0;
uint16_t Buzzer::m_cycle_time = 1;
uint8_t Buzzer::m_pin_num = 0;

/***************************************************
 * 初始化
 * buzzer_num为蜂鸣器的引脚
 * cycle_time为蜂鸣器控制的精度 ms
 */
Buzzer::Buzzer(uint8_t buzzer_num, uint16_t cycle_time)
{
    m_count = 0;
    m_pin_num = buzzer_num;
    m_cycle_time = cycle_time != 0 ? cycle_time : 1;
}

bool Buzzer::start()
{
    pinMode(m_pin_num, OUTPUT);
    digitalWrite(m_pin_num, BEEP_OFF); // 默认关闭蜂鸣器

    // ledcSetup(BEEP_CHANNEL, 5000, 8);
    // ledcAttachPin(m_pin_num, BEEP_CHANNEL);
    // ledcWrite(BEEP_CHANNEL, (int)(0.8 * 255));
    return true;
}

void Buzzer::timer_handler(TimerHandle_t xTimer)
{
    if (0 < m_count)
    {
        --m_count;
    }
    else
    {
        digitalWrite(m_pin_num, BEEP_OFF); // 定时时间到了 关闭蜂鸣器
    }
}

Buzzer::~Buzzer()
{
}

/****************************************
 * 设置长鸣时间
 * time为长鸣时间 ms
 *****************************************/
void Buzzer::set_beep_time(uint16_t time)
{
    m_count = time / m_cycle_time;
    if (0 < m_count)
    {
        digitalWrite(m_pin_num, BEEP_ON); // 开始定时 开启蜂鸣器
    }
}