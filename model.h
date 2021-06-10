

/*

全局引用文件


*/
typedef unsigned char u8, *pu8;
typedef unsigned short u16, *pu16;
typedef unsigned int u32, *pu32;
typedef unsigned long long u64, *pu64;
typedef char s8, *ps8;
typedef short s16, *ps16;
typedef long s32, *ps32;
typedef long long s64, *ps64;
typedef void *pvoid;

typedef enum _sym_typ {
    sym_typ_const,
    sym_typ_ident, 
    sym_typ_stmt 
} sym_typ;

// Constants
typedef struct _sym_const {
    int value;
} sym_const;

// Identifiers
typedef struct _sym_ident {
    int index;
} sym_ident;

// Expressions
typedef struct _sym_stmt {
    int type;
    int sym_count;
    struct _sym *sym_list[1];
} sym_stmt;

typedef struct _sym {
    sym_typ type;
    union {
        sym_const con;
        sym_ident ident;
        sym_stmt stmt;
    };
} sym;




  enum tokentype //中间代码的标识
  {
    INT = 258,
    STR = 259,
    VAR_LINT = 260,
    VAR_GINT = 261,
    FN_NAME = 262,
    LOOP = 263,
    IF = 264,
    WRITE_STR = 265,
    WRITE_INT = 266,
    READ_INT = 267,
    WRITE_NEWLINE = 268,
    FUNCTION = 269,
    BREAK = 270,
    FN_DEF = 271,
    FN_CALL = 272,
    IFX = 273,
    ELSE = 274,
    EQ = 275,
    UMINUS = 276
  };

#define CEED_DATA_SECTION_VA            0x600000        // 16MB
#define CEED_CODE_SECTION_VA            0x700000        // 16MB
#define CEED_RDATA_SECTION_VA           0x800000        // 16MB

#define CEED_FILE_ALIGN                 0x1000
#define CEED_SECTION_ALIGN              0x1000



#define CEED_MAX_SECTION_COUNT          0x8

extern int func[26];

u32 emit_code(sym *p);
void emit8(u8 i);
void emit16(u16 i);
void emit32(u32 i);
void emit64(long i);
void elf_header64(FILE *fp,  int phnum, int shnum) ;

void program_header64(FILE *fp, int sec, long offset, long vaddr, long filesz,long memsz);
#define round_up(n, r) ((((n) + ((r)-1))/(r))*(r))

u32 add_str(pu8 str);
long
add_str64(pu8 str);
void cmplr_init();
void elf_init();
void pe_init();

typedef void (*pfn_gen_exe_file)(pvoid ei);
typedef pvoid (*pfn_set_exe_scn)(pvoid ei, pu8 scn_data, u32 scn_size);
typedef pvoid (*pfn_get_va)(pvoid ei);
typedef void (*pfn_emit_main_init)();
typedef void (*pfn_emit_main_exit)();
typedef void (*pfn_emit_write)(u32 buf_addr, u32 buf_len);
typedef void (*pfn_emit_write_reg_input)();
typedef void (*pfn_emit_read)(u32 buf_addr, u32 buf_len);

extern pvoid ei;
extern pfn_gen_exe_file gen_exe_file;
extern pfn_set_exe_scn set_exe_code_scn;
extern pfn_set_exe_scn set_exe_rdata_scn;
extern pfn_get_va get_code_va;
extern pfn_get_va get_data_va;
extern pfn_get_va get_rdata_va;
extern pfn_emit_main_init emit_main_init;
extern pfn_emit_main_exit emit_main_exit;
extern pfn_emit_write emit_write;
extern pfn_emit_write_reg_input emit_write_reg_input;
extern pfn_emit_read emit_read;

