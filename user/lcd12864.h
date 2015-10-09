
// �����

void Delay(volatile uint32_t nCount) {
    for (; nCount != 0; nCount--);
}

// ������ ����� � ��

void LcdByte(uint32_t byte)
{
	GPIOC->ODR = byte;	   	// ����� � ����
	Delay(0x000F);		   	// ����� 1 ���
	GPIOC->BSRR = GPIO_BSRR_BS9;    // ���������� �
	Delay(0x000F);		   	// ����� 1 ���
	GPIOC->BSRR = GPIO_BSRR_BR9;	// ���������� �
	Delay(0x000F);		   	// ����� 1 ���
}

void CodeL(uint32_t code)
{
	code |= 0x0900;    // �������� ��� ���� � �������� � ����� ��������
	LcdByte(code);
}

void CodeR(uint32_t code)
{
	code |= 0x1100;    // �������� ��� ���� � �������� � ������ ��������
	LcdByte(code);
}

void DataL(uint32_t code)
{
	code |= 0x2900;    // �������� ��� ������ � �������� � ����� ��������
 	LcdByte(code);
}

void DataR(uint32_t code)
{
	code |= 0x3100;    // �������� ��� ������ � �������� � ������ ��������
	LcdByte(code);
}


