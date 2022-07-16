/*
 */

 #define F_CPU      16000000UL

#include <avr/io.h>
#include <util/delay.h>

// UART 통신 속도
#define USART_BAUDRATE      9600
// 우선 테스트 후에 한 번에 설명 ???????????
// UART의 최대 단점은 무엇일까 ? 오차율이 있다.
// 16000000 / (16 * 9600)
// 11  10  9   8   7   6   5   4   3   2   1   0
// 11 ~ 8번 비트까지를 얻고자 한다면 하위 8 비트를 밀어야함
// 남은 8비트는 그대로 사용하면 됨
#define BAUD_PRESCALE       (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// USART 모드 선택
// 동기 방식이란 ? 클럭의 업다운에 의해 시작과 끝을 결정하게 됨
//              또한 데이터의 처리 역시 동기 방식을 취할 수 있음
//              그러나 최근 트렌드에서는 속도 측면 때문에
//              시작과 끝을 동기 처리하고 중간 데이터는 비동기로 처리하는 편(하이브리드 방식)이다.
// 비동기 방식이란 ? 클럭의 업다운에 영향을 받지 않고
//                처리가 가능한 선에서 최대한 빨리 여러 데이터들을 처리하는 방식이다.
#define ASYNCHRONOUS        (0 << UMSEL00)

// USART PARITY 비트를 선택
#define DISABLED            (0 << UPM00)
#define EVEN_PARITY         (2 << UPM00)
#define ODD_PARITY          (3 << UPM00)
#define PARITY_MODE         DISABLED

// USART STOP 비트 선택
#define ONE_BIT             (0 << USBS0)
#define TWO_BIT             (1 << USBS0)
#define STOP_BIT            ONE_BIT

// USART DATA 비트 선택
#define FIVE_BIT            (0 << UCSZ00)
#define SIX_BIT             (1 << UCSZ00)
#define SEVEN_BIT           (2 << UCSZ00)
#define EIGHT_BIT           (3 << UCSZ00)
#define DATA_BIT            EIGHT_BIT

void USART_Init ()
{
    // 통신 속도 설정
    UBRR0H = BAUD_PRESCALE >> 8;
    UBRR0L = BAUD_PRESCALE;

    // 프레임 포맷 설정
    // 비동기 방식으로 패리티는 사용하지 않고 정지를 알리는 비트 1개와 8개의 데이터비트로 구성된다.
    UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;

    // 인터럽트 빈도수가 높은 경우 Bottom Half 정책을 사용
    // 송수신 허용
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void USART_TransmitPolling(uint8_t DataByte)
{
    // UDR 데이터 준비 이전까지 구동하지 않음
    while (( UCSR0A & (1 <<UDRE0)) == 0) {}

    UDR0 = DataByte;
}

int main(void)
{
    USART_Init();

    while(1)
    {
        USART_TransmitPolling('E');
        USART_TransmitPolling('M');
        USART_TransmitPolling('B');
        USART_TransmitPolling('E');
        USART_TransmitPolling('D');
        USART_TransmitPolling('D');
        USART_TransmitPolling('E');
        USART_TransmitPolling('D');
        USART_TransmitPolling(' ');
        USART_TransmitPolling('M');
        USART_TransmitPolling('A');
        USART_TransmitPolling('S');
        USART_TransmitPolling('T');
        USART_TransmitPolling('E');
        USART_TransmitPolling('R');
        USART_TransmitPolling(' ');
        USART_TransmitPolling('C');
        USART_TransmitPolling('O');
        USART_TransmitPolling('U');
        USART_TransmitPolling('R');
        USART_TransmitPolling('S');
        USART_TransmitPolling('E');
        USART_TransmitPolling('!');
        USART_TransmitPolling('\r');
        USART_TransmitPolling('\n');
        USART_TransmitPolling('\0');
        /* delay.h에 문제가 있을 경우
        int i = 0;   <<<--- 상위에 선언해야함

        for(; i < 99999999; i++)
            ;
        */
        _delay_ms(1000);
    }

    return 0;
}
