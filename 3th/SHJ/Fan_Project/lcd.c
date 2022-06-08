#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>

// 데이터 핀 연결 포트
#define PORT_DATA                       PORTD
// 제어 핀 연결 포트
#define PORT_CONTROL                    PORTB
// 데이터 핀의 데이터 방향
#define DDR_DATA                        DDRD
// 제어 핀의 데이터 방향
#define DDR_CONTROL                     DDRB
// RS 제어 핀의 비트 번호
#define RS_PIN                          0
// E 제어 핀의 비트 번호
#define E_PIN                           1

#define COMMAND_CLEAR_DISPLAY           0x01
// 8비트, 2라인, 5x8 폰트
#define COMMAND_8_BIT_MODE              0x38
// 4비트, 2라인, 5x8 폰트
#define COMMAND_4_BIT_MODE              0x28

#define COMMAND_DISPLAY_ON_OFF_BIT     2
#define COMMAND_CURSOR_ON_OFF_BIT       1
#define COMMAND_BLINK_ON_OFF_BIT        0

// Falling 엣지에서 동작
void lcd_pulse_enable (void)
{
    // E를 HIGH로
    PORT_CONTROL |= (1 << E_PIN);
    _delay_ms(1);
    // E를 LOW로
    PORT_CONTROL &= ~(1 << E_PIN);
    _delay_ms(1);
}

void lcd_write_data (uint8_t data)
{
    // 문자 출력에서 RS는 1
    PORT_CONTROL |= (1 << RS_PIN);
    // 출력할 문자 데이터
    PORT_DATA = data;
    // 문자 출력
    lcd_pulse_enable();
}

void lcd_write_command (uint8_t command)
{
    // 명령어 실행에서 RS는 0
    PORT_CONTROL &= ~(1 << RS_PIN);
    // 데이터 핀에 명령어 전달
    PORT_DATA = command;
    // 명령어 실행
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

    // 연결 핀을 출력으로 설정
    DDR_DATA = 0xFF;
    DDR_CONTROL |= (1 << RS_PIN) | (1 << E_PIN);

    // 8 비트 모드
    lcd_write_command(COMMAND_8_BIT_MODE);

    // display ON/OFF 제어
    // 화면 on, 커서 off, 커서 깜빡임 off
    uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
    lcd_write_command(command);

    // 화면 지움
    lcd_clear();

    // Entry Mode Set
    // 출력 후 커서를 오른쪽으로 옮김
    // 즉 DDRAM의 주소가 증가하며 화면 이동은 없음
    lcd_write_command(0x06);
}

void lcd_write_string (char *string)
{
    uint8_t i;

    // 종료 문자 만날 때까지
    for (i = 0; string[i]; i++)
    {
        // 문자 단위 출력
        lcd_write_data(string[i]);
    }
}

void lcd_goto_xy (uint8_t row, uint8_t col)
{
    // [0, 15]
    col %= 16;
    // [0, 1]
    row %= 2;

    // 첫 라인 시작 주소는 0x00
    // 두번째 라인 시작 주소는 0x40
    uint8_t address = (0x40 * row) + col;
    uint8_t command = 0x80 + address;

    // 커서 이동
    lcd_write_command(command);
}

int lcd_mode (void)
{
    lcd_init();

    lcd_write_string("Hello World!");
    _delay_ms(1000);

    lcd_clear();

    // 화면에 보이는 영역은 디폴트 값으로 0 ~ 1행
    // 0 ~ 15열로 설정되어 있다.
    lcd_goto_xy(0, 0);          // 0행, 0열로 이동
    lcd_write_data('1');        // 문자 단위 출력
    lcd_goto_xy(0, 5);
    lcd_write_data('2');
    lcd_goto_xy(1, 0);
    lcd_write_data('3');
    lcd_goto_xy(1, 5);
    lcd_write_data('4');

    while(1)
    {
        ;
    }

    return 0;
}

