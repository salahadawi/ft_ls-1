# libft
basic c library written by me at Hive Helsinki. We are required to write out own functions to deepen our knowledge. This in an ongoing project that started with basic functions but I'm adding new useful ones in every project I make.

## The libft project
[Subject for this project](libft.en.pdf)

### Basic functions required in the libft project:
- ft_putchar
- ft_putchar_fd
- ft_putstr
- ft_putstr_fd
- ft_putnbr
- ft_putnbr_fd
- ft_putendl
- ft_putendl_fd
- ft_strlen
- ft_itoa
- ft_strdup
- ft_strcpy
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memccpy
- ft_memmove
- ft_memcmp
- ft_strncpy
- ft_strcat
- ft_memchr
- ft_strncat
- ft_strlcat
- ft_strchr
- ft_strrchr
- ft_strstr
- ft_strnstr
- ft_strcmp
- ft_strncmp
- ft_atoi
- ft_isalpha
- ft_isdigit
- ft_isalnum
- ft_isascii
- ft_isprint
- ft_toupper
- ft_tolower
- ft_memalloc
- ft_memdel
- ft_strnew
- ft_strdel
- ft_strclr
- ft_striter
- ft_striteri
- ft_strmap
- ft_strmapi
- ft_strequ
- ft_strnequ
- ft_strsub
- ft_strjoin
- ft_strtrim
- ft_strsplit

### Basic list functions required in the libft project with few own add ons
- ft_lstnew
- ft_lstdelone
- ft_lstdel
- ft_lstadd
- ft_lstiter
- ft_lstmap
- ft_lstsrc
- ft_lstnewtoend
- ft_lstend
- ft_lstaddafter

### My own add ons to the library
- ft_dynamic_string     *//dynamic allocation when adding more characters to a string*
- ft_addstr             *//adding a string to a string array and allocating enough space for it*
- ft_define_length      *//defines how many digits the is to a integer number*
- ft_is_whitespace      *//returns the index of  the first whitespace*
- ft_str_realloc        *//reallocs a new string made from starting index to ending index of the old one*
- ft_strset             *//creates a new string of given nunmber of characters, initialized with given character*
- ft_strpaste           *//pastes the characters of a string, does not include nullbyte. can be used to insert string inside a string*
- ft_strjoin_frees2     *//joins two strings and frees one of them*
- ft_strpaste_digits    *//pastes only digits from given string to destination*
- ft_char_str_join      *//joins two character strings*
- ft_strsub_freestr     *//returns a string starting from given index with the length given, and frees the given string*
- ft_strpaste_end       *//pastes the source string to the end of the destination string*
- ft_str_char_join      *//appends a string with a given character*
