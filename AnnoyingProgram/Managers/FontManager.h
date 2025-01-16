﻿#pragma once
#include "../Common/CommonLib.h"

class FontManager
{
public:
    FontManager() = default;
    static const sf::Font& get_font_by_name(const sf::String& name, bool fallback = true);
    static const sf::Font& get_fallback_font();
    static const sf::Font& get_random_font();
private:
    std::map<sf::String, sf::Font> fonts_;
    static FontManager instance_;

    
    std::vector<sf::String> font_names_ = {
    "arial",
    "ariblk",
    "arialbd",
    "arialbi",
    "ariali",
    "bahnschrift",
    "calibri",
    "calibrib",
    "calibriz",
    "calibrii",
    "calibril",
    "calibrili",
    "cambria.ttc",
    "cambriab",
    "cambriaz",
    "cambriai",
    "candara",
    "candarab",
    "candaraz",
    "candarai",
    "candaral",
    "candarali",
    "comic",
    "comicbd",
    "comicz",
    "comici",
    "consola",
    "consolab",
    "consolaz",
    "consolai",
    "constan",
    "constanb",
    "constanz",
    "constani",
    "corbel",
    "corbelb",
    "corbelz",
    "corbeli",
    "corbell",
    "corbelli",
    "cour",
    "courbd",
    "courbi",
    "couri",
    "ebrima",
    "ebrimabd",
    "framd",
    "framdit",
    "Gabriola",
    "gadugi",
    "gadugib",
    "georgia",
    "georgiab",
    "georgiaz",
    "georgiai",
    "impact",
    "Inkfree",
    "javatext",
    "leelawui",
    "leelauib",
    "leeluisl",
    "lucon",
    "l_10646",
    "malgun",
    "malgunbd",
    "malgunsl",
    "himalaya",
    "msjh.ttc",
    "msjhbd.ttc",
    "msjhl.ttc",
    "ntailu",
    "ntailub",
    "phagspa",
    "phagspab",
    "micross",
    "taile",
    "taileb",
    "msyh.ttc",
    "msyhbd.ttc",
    "msyhl.ttc",
    "msyi",
    "mingliub.ttc",
    "modern.fon",
    "monbaiti",
    "msgothic.ttc",
    "mvboli",
    "mmrtext",
    "mmrtextb",
    "Nirmala",
    "NirmalaB",
    "NirmalaS",
    "pala",
    "palab",
    "palabi",
    "palai",
    "roman.fon",
    "SansSerifCollection",
    "script.fon",
    "SegoeIcons",
    "segmdl2",
    "segoepr",
    "segoeprb",
    "segoesc",
    "segoescb",
    "segoeui",
    "seguibl",
    "seguibli",
    "segoeuib",
    "segoeuiz",
    "seguiemj",
    "seguihis",
    "segoeuii",
    "segoeuil",
    "seguili",
    "seguisb",
    "seguisbi",
    "segoeuisl",
    "seguisli",
    "seguisym",
    "SegUIVar",
    "simsun.ttc",
    "simsunb",
    "SitkaVF",
    "SitkaVF-Italic",
    "sylfaen",
    "symbol",
    "tahoma",
    "tahomabd",
    "times",
    "timesbd",
    "timesbi",
    "timesi",
    "trebuc",
    "trebucbd",
    "trebucbi",
    "trebucit",
    "verdana",
    "verdanab",
    "verdanaz",
    "verdanai",
    "webdings",
    "wingding",
    "YuGothB.ttc",
    "YuGothL.ttc",
    "YuGothM.ttc",
    "YuGothR.ttc",
    "COURE.FON",
    "COURF.FON",
    "SERIFE.FON",
    "SERIFF.FON",
    "SSERIFE.FON",
    "SSERIFF.FON",
    "SMALLE.FON",
    "SMALLF.FON",
    "holomdl2",
    "AGENCYB",
    "AGENCYR",
    "ALGER",
    "ANTQUAB",
    "ANTQUABI",
    "ANTQUAI",
    "ARIALN",
    "ARIALNB",
    "ARIALNBI",
    "ARIALNI",
    "ARLRDBD",
    "BASKVILL",
    "BAUHS93",
    "BELL",
    "BELLB",
    "BELLI",
    "BERNHC",
    "BKANT",
    "BOD_B",
    "BOD_BI",
    "BOD_BLAI",
    "BOD_BLAR",
    "BOD_CB",
    "BOD_CBI",
    "BOD_CI",
    "BOD_CR",
    "BOD_I",
    "BOD_PSTC",
    "BOD_R",
    "BOOKOS",
    "BOOKOSB",
    "BOOKOSBI",
    "BOOKOSI",
    "BRADHITC",
    "BRITANIC",
    "BRLNSB",
    "BRLNSDB",
    "BRLNSR",
    "BROADW",
    "BRUSHSCI",
    "BSSYM7",
    "CALIFB",
    "CALIFI",
    "CALIFR",
    "CALIST",
    "CALISTB",
    "CALISTBI",
    "CALISTI",
    "CASTELAR",
    "CENSCBK",
    "CENTAUR",
    "CENTURY",
    "CHILLER",
    "COLONNA",
    "COOPBL",
    "COPRGTB",
    "COPRGTL",
    "CURLZ___",
    "DUBAI-BOLD",
    "DUBAI-LIGHT",
    "DUBAI-MEDIUM",
    "DUBAI-REGULAR",
    "ELEPHNT",
    "ELEPHNTI",
    "ENGR",
    "ERASBD",
    "ERASDEMI",
    "ERASLGHT",
    "ERASMD",
    "FELIXTI",
    "FORTE",
    "FRABK",
    "FRABKIT",
    "FRADM",
    "FRADMCN",
    "FRADMIT",
    "FRAHV",
    "FRAHVIT",
    "FRAMDCN",
    "FREESCPT",
    "FRSCRIPT",
    "FTLTLT",
    "GARA",
    "GARABD",
    "GARAIT",
    "GIGI",
    "GILBI___",
    "GILB____",
    "GILC____",
    "GILI____",
    "GILLUBCD",
    "GILSANUB",
    "GIL_____",
    "GLECB",
    "GLSNECB",
    "GOTHIC",
    "GOTHICB",
    "GOTHICBI",
    "GOTHICI",
    "GOUDOS",
    "GOUDOSB",
    "GOUDOSI",
    "GOUDYSTO",
    "HARLOWSI",
    "HARNGTON",
    "HATTEN",
    "HTOWERT",
    "HTOWERTI",
    "IMPRISHA",
    "INFROMAN",
    "ITCBLKAD",
    "ITCEDSCR",
    "ITCKRIST",
    "JOKERMAN",
    "JUICE___",
    "KUNSTLER",
    "LATINWD",
    "LBRITE",
    "LBRITED",
    "LBRITEDI",
    "LBRITEI",
    "LCALLIG",
    "LEELAWAD",
    "LEELAWDB",
    "LFAX",
    "LFAXD",
    "LFAXDI",
    "LFAXI",
    "LHANDW",
    "LSANS",
    "LSANSD",
    "LSANSDI",
    "LSANSI",
    "LTYPE",
    "LTYPEB",
    "LTYPEBO",
    "LTYPEO",
    "MAGNETOB",
    "MAIAN",
    "MATURASC",
    "MISTRAL",
    "MOD20",
    "MSUIGHUB",
    "MSUIGHUR",
    "MTCORSVA",
    "MTEXTRA",
    "NIAGENG",
    "NIAGSOL",
    "OCRAEXT",
    "OLDENGL",
    "ONYX",
    "PALSCRI",
    "PAPYRUS",
    "PARCHM",
    "PERBI___",
    "PERB____",
    "PERI____",
    "PERTIBD",
    "PERTILI",
    "PER_____",
    "PLAYBILL",
    "POORICH",
    "PRISTINA",
    "RAGE",
    "RAVIE",
    "REFSAN",
    "REFSPCL",
    "ROCCB___",
    "ROCC____",
    "ROCK",
    "ROCKB",
    "ROCKBI",
    "ROCKEB",
    "ROCKI",
    "SCHLBKB",
    "SCHLBKBI",
    "SCHLBKI",
    "SCRIPTBL",
    "SHOWG",
    "SNAP____",
    "STENCIL",
    "TCBI____",
    "TCB_____",
    "TCCB____",
    "TCCEB",
    "TCCM____",
    "TCMI____",
    "TCM_____",
    "TEMPSITC",
    "VINERITC",
    "VIVALDII",
    "VLADIMIR",
    "WINGDNG2",
    "WINGDNG3",
    "Neo Sans",
    "CascadiaCode",
    "CascadiaMono",
    "AMGDT___",
    "complex_IV25",
    "complex_IV50",
    "gdt_IV25",
    "GOST Common Italic",
    "isocp3_IV25",
    "GOST Common",
    "greeks_IV25",
    "gdt_IV50",
    "isocp_IV25",
    "GENISO",
    "greekc_IV25",
    "greekc_IV50",
    "greeks_IV50",
    "AcadEref",
    "scripts_IV25",
    "isocp_IV50",
    "isocp2_IV25",
    "symap_IV25",
    "scripts_IV50",
    "isocp2_IV50",
    "isocp3_IV50",
    "symath_IV50",
    "isocpeui",
    "isocpeur",
    "txt_IV25",
    "isoct2_IV25",
    "txt_IV50",
    "symath_IV25",
    "isoct2_IV50",
    "symusic_IV50",
    "isoct3_IV25",
    "Amgdt_IV25",
    "isoct3_IV50",
    "AIGDT___",
    "isoct_IV25",
    "isoct_IV50",
    "italic_IV25",
    "italic_IV50",
    "monotxt_IV25",
    "monotxt_IV50",
    "symap_IV50",
    "romans_IV25",
    "simplex_IV25",
    "romans_IV50",
    "simplex_IV50",
    "syastro_IV25",
    "syastro_IV50",
    "symeteo_IV25",
    "symeteo_IV50",
    "symusic_IV25",
    "AMDT_Symbols",
    "Amgdt_IV50",
    "isocteur",
    "isocteui",
    "unispace bd",
    "Inter_FXH-Bold",
    "Inter_FXH-BoldItalic",
    "Inter_FXH-Italic",
    "Inter_FXH-Regular",
    "OUTLOOK",
    "LatoWeb-Bold",
    "LatoWeb-BoldItalic",
    "LatoWeb-Italic",
    "LatoWeb-Light",
    "LatoWeb-LightItalic",
    "LatoWeb-Regular",
    "LatoWeb-Semibold",
    "LatoWeb-SemiboldItalic",
    "SimsunExtG"
    };
};
