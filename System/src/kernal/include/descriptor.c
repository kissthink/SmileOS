
void loadGdtr(int limit, int addr);

void loadIdtr(int limit, int addr);

void setGlobalDescriptor(int descNumber, u32 limit, int base, int ar)
{
	if (limit>0xFFFFF) {
		ar |= 0x8000;
		limit/=0x1000;	
	}

	GlobalDescriptor *gdtBase = (GlobalDescriptor *)ADDRESS_GDT;
	(*(gdtBase+descNumber)).limitLow = limit & 0xFFFF;
	(*(gdtBase+descNumber)).baseLow = base & 0xFFFF;
	(*(gdtBase+descNumber)).baseMid = (base>>16) & 0xFFFF;
	(*(gdtBase+descNumber)).limitHigh = ((limit>>16) & 0x0F) | ((ar>>8) & 0xF0);
	(*(gdtBase+descNumber)).baseHigh = (base>>24) & 0xFF;
}

void setInterruptDescriptor(int intNumber, int offset, int selector, int ar) 
{
	GateDescriptor *idtBase = (GateDescriptor *)ADDRESS_IDT;
	(*(idtBase+intNumber)).offsetLow = offset & 0xFFFF;
	(*(idtBase+intNumber)).selector = selector;
	(*(idtBase+intNumber)).dwCount = (ar>>8) & 0xFF;
	(*(idtBase+intNumber)).accessRight = ar & 0xFF;
	(*(idtBase+intNumber)).offsetHigh = (offset>>16) & 0xFFFF;
}
