#include <cstdio>
#include <cstring>

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		puts("Usage: kg <name>");
		return 1;
	}

	const char* name = argv[1];
	size_t length = strlen(name);

	if (length <= 3)
	{
		puts("Length of the name must be > 3");
		return 2;
	}

	int tab_1[15] = {
		0x16, 0x99, 0x11, 0x63, 0x15, 0x54, 0x52, 0x88,
		0x01, 0x31, 0x56, 0x68, 0x55, 0x37, 0x00
	};
	int tab_2[15] = {
		0x13, 0x16, 0x99, 0x11, 0x63, 0x15, 0x54, 0x52,
		0x88, 0x01, 0x31, 0x56, 0x68, 0x55, 0x37
	};

	char serial[100];
	int eax, edx, ecx, val = 0, val2 = 0;
	length = length > 14 ? 14 : length;
	for (size_t i = 0; i < length; i++)
	{
		ecx = name[i];
		eax = (tab_1[i] & 0xff);
		eax += val;
		eax += ecx;
		val = eax;
		edx = name[i];
		edx *= 10;
		eax = val;
		eax += edx;
		val = eax;
	}
	for (size_t i = 0; i < length; i++)
	{
		ecx = (tab_2[i] & 0xff);
		ecx *= 10;
		edx = val2;
		edx += ecx;
		val2 = edx;
		eax = name[2];
		edx = (tab_2[i] & 0xff);
		edx += val2;
		edx += eax;
		val2 = edx;
		eax = val2;
		eax += 0x31337;
		val2 = eax;
	}
	sprintf_s(serial, "%X-aboo-me-%X%i-SCA", val, val2, val2);
	printf("NAME: %s\nSERIAL: %s\n", name, serial);
	return 0;
}
