#include "spi.h"

void spi_init (void)
{

    DDRB |= (1 << SPI_SS);

    PORTB |= (1 << SPI_SS);

    DDRB |= (1 << SPI_MOSI);

    DDRB &= ~(1 << SPI_MISO);

    DDRB |= (1 << SPI_SCK);

    SPCR |= (1 << MSTR);

    SPCR |= (1 << SPE);
}

void eeprom_change_byte (uint8_t byte)
{

    SPDR = byte;

    loop_until_bit_is_set(SPSR, SPIF);
}

void eeprom_send_address (uint8_t address)
{
    eeprom_change_byte(address);
}

uint8_t eeprom_read_status (void)
{

    EEPROM_SELECT();

    eeprom_change_byte(EEPROM_RDSR);

    eeprom_change_byte(0);

    EEPROM_DESELECT();

    return SPDR;
}

void eeprom_write_enable (void)
{

    EEPROM_SELECT();

    eeprom_change_byte(EEPROM_WREN);


    EEPROM_DESELECT();
}

uint8_t eeprom_read_byte (uint8_t address)
{
    EEPROM_SELECT();

    eeprom_change_byte(EEPROM_READ);

    eeprom_send_address(address);

    eeprom_change_byte(0);

    EEPROM_DESELECT();

    return SPDR;
}

void eeprom_write_byte(uint8_t address, uint8_t data)
{

    eeprom_write_enable();

    EEPROM_SELECT();

    eeprom_change_byte(EEPROM_WRITE);

    eeprom_send_address(address);

    eeprom_change_byte(data);

    EEPROM_DESELECT();

    while (eeprom_read_status() & _BV(EEPROM_WRITE_IN_PROGRESS))
    {
        ;
    }
}

