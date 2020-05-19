#include <cstdio>
#include <cstring>


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        puts("Usage: kg <name>");
        return 1;
    }

    const char* name = argv[1];
    size_t name_len = strlen(name);

    if (name_len <= 3 || name_len >= 15)
    {
        puts("3 < name < 15");
        return 2;
    }

    int mod_name_len = 2 * name_len;
    char* mod_name = new char[mod_name_len];
    for (size_t i = 0, i2 = 0; i2 < name_len; i += 2, i2++)
    {
        mod_name[i] = name[i2];
        mod_name[i + 1] = ' ';
    }


    unsigned char str[35] = "-[#]]=}&&&+(=$*,,)&.*/+++[][;/.. 0";
    str[32] = 0xA7;
    int str_len = 34;
    for (int i = 0; i < str_len; i++)
    {
        str[i]++;
    }

    for (int i = 0; i < mod_name_len; i++)
    {
        str[i] ^= mod_name[i];
    }

    unsigned char reversed_str[35];
    int reversed_str_len = str_len;
    for (int i = str_len - 1, i2 = 0; i >= 0; i--, i2++)
    {
        reversed_str[i2] = str[i];
    }

    unsigned char buf[35];
    int buf_len = str_len;
    for (int i = 0, i2 = 0; i < reversed_str_len; i += 2, i2++)
    {
        buf[i] = reversed_str[i2];
        buf[i + 1] = str[i2];
        if (buf[i2] <= 0x1F || buf[i2] > 0x7A)
        {
            buf[i2] = 0x36;
        }
    }

    char* serial = new char[name_len + 1];
    serial[name_len] = '\0';
    for (int i = 0; i < name_len; i++)
    {
        serial[i] = buf[i];
    }

    printf("%s %s\n", name, serial);

    delete[] serial;
    delete[] mod_name;
    return 0;
}