uint64_t str2u64(const char *value)
{
   uint64_t result = 0;

   size_t const length = strlen(value);
   switch (length) {
     case 20:    result += (value[length - 20] - '0') * 10000000000000000000ULL;
     case 19:    result += (value[length - 19] - '0') * 1000000000000000000ULL;
     case 18:    result += (value[length - 18] - '0') * 100000000000000000ULL;
     case 17:    result += (value[length - 17] - '0') * 10000000000000000ULL;
     case 16:    result += (value[length - 16] - '0') * 1000000000000000ULL;
     case 15:    result += (value[length - 15] - '0') * 100000000000000ULL;
     case 14:    result += (value[length - 14] - '0') * 10000000000000ULL;
     case 13:    result += (value[length - 13] - '0') * 1000000000000ULL;
     case 12:    result += (value[length - 12] - '0') * 100000000000ULL;
     case 11:    result += (value[length - 11] - '0') * 10000000000ULL;
     case 10:    result += (value[length - 10] - '0') * 1000000000ULL;
     case  9:    result += (value[length -  9] - '0') * 100000000ULL;
     case  8:    result += (value[length -  8] - '0') * 10000000ULL;
     case  7:    result += (value[length -  7] - '0') * 1000000ULL;
     case  6:    result += (value[length -  6] - '0') * 100000ULL;
     case  5:    result += (value[length -  5] - '0') * 10000ULL;
     case  4:    result += (value[length -  4] - '0') * 1000ULL;
     case  3:    result += (value[length -  3] - '0') * 100ULL;
     case  2:    result += (value[length -  2] - '0') * 10ULL;
     case  1:    result += (value[length -  1] - '0');
   }
   return result;
}
