void lcd_begin(){
	uint8_t display_function;
	display_function |= 0x08;



}
uint16_t command(uint8_t d1){
	uint16_t wd = ((uint16_t) 0x80 << 8) | d1;
	return wd;
}

uint16_t write_com(uint8_t d1){
	uint16_t wd = ((uint16_t) 0x40 << 8) | d1;
	return wd;
}

