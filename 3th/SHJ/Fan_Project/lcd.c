#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PORT_DATA                       PORTC

#define PORT_CONTROL                    PORTA

#define DDR_DATA                        DDRC

#define DDR_CONTROL                     DDRA

#define RS_PIN                          0

#define E_PIN                           1

#define COMMAND_CLEAR_DISPLAY           0x01

#define COMMAND_8_BIT_MODE              0x38

#define COMMAND_4_BIT_MODE              0x28

#define COMMAND_DISPLAY_ON_OFF_BIT     2
#define COMMAND_CURSOR_ON_OFF_BIT       1
#define COMMAND_BLINK_ON_OFF_BIT        0


void lcd_pulse_enable (void)
{

    PORT_CONTROL |= (1 << E_PIN);
    _delay_ms(1);

    PORT_CONTROL &= ~(1 << E_PIN);
    _delay_ms(1);
}

void lcd_write_data (uint8_t data)
{

    PORT_CONTROL |= (1 << RS_PIN);

    PORT_DATA = data;

    lcd_pulse_enable();
}

void lcd_write_command (uint8_t command)
{

    PORT_CONTROL &= ~(1 << RS_PIN);

    PORT_DATA = command;

    lcd_pulse_enable();
}

void lcd_clear (void)
{
    lcd_write_command(COMMAND_CLEAR_DISPLAY);
    _delay_ms(2);
}

void lcd_init (void)
{
    _delay_ms(50);

    DDR_DATA = 0xFF;
    DDR_CONTROL |= (1 << RS_PIN) | (1 << E_PIN);

    lcd_write_command(COMMAND_8_BIT_MODE);

    uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
    lcd_write_command(command);

    lcd_clear();

    lcd_write_command(0x06);
}

void lcd_write_string (char *string)
{
    uint8_t i;

    lcd_clear();

    for (i = 0; string[i]; i++)
    {
        lcd_write_data(string[i]);
    }
}

void lcd_goto_xy (uint8_t row, uint8_t col)
{
    col %= 16;

    row %= 2;

    uint8_t address = (0x40 * row) + col;
    uint8_t command = 0x80 + address;

    lcd_write_command(command);
}





