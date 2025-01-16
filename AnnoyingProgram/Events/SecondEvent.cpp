#include "SecondEvent.h"


MovingWindow::MovingWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings) : WindowManager(mode, title, style, settings)
{
    thread = new sf::Thread(&MovingWindow::move, this);
}

MovingWindow::~MovingWindow()
{
    WindowManager::~WindowManager();
    delete thread;
}

void MovingWindow::tick(const double delta_time)
{
    WindowManager::tick(delta_time);
    if (velocity == sf::Vector2f(0, 0)) return;

    if(processing.load()) return;
    
    last_dt = delta_time;

    //delete thread;

    //thread = new sf::Thread(&MovingWindow::move, this);
    processing.store(true);
    thread->launch();
}

void MovingWindow::move()
{
    const auto bounds = sf::Vector2i(sf::VideoMode::getDesktopMode().width - getSize().x,
                                 sf::VideoMode::getDesktopMode().height - getSize().y);
    auto new_pos = getPosition() + static_cast<sf::Vector2i>(static_cast<float>(last_dt) * velocity);
    if (new_pos.x > bounds.x || new_pos.x < 0)
    {
        velocity.x *= -1;
        new_pos.x = clamp(new_pos.x, 0, bounds.x);
    }
    if (new_pos.y > bounds.y || new_pos.y < 0)
    {
        velocity.y *= -1;
        new_pos.y = clamp(new_pos.y, 0, bounds.y);
    }

    setPosition(new_pos);
    processing.store(false);
}

SecondEvent::SecondEvent()
{
    possible_texts = {
        "Close me",
        "Close this",
        "HELLO!",
        "Hey there!",
        "Hello there!",
        "Hello <3",
        "Hello! :)",
        "I love you!",
        "Love you :)",
        "Hey!",
        "UwU",
        
    };
    
    font_names = {
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
}

void SecondEvent::start()
{
    anti_taskbar = new AntiTaskbar;
    windows.reserve(10);
    for(int i = 0; i < 10; i++)
        create_window();
}

void SecondEvent::end()
{
    anti_taskbar->mark_for_deletion();
    for(const auto w : windows)
        w->mark_for_deletion();
}

#define WINDOW_OPEN_DELAY 1.
void SecondEvent::tick(const double delta_time)
{
    if(second_phase) return;
    if((current_tick_time += delta_time) > WINDOW_OPEN_DELAY &&running)
    {
        create_window();
        current_tick_time -= WINDOW_OPEN_DELAY;
    }
}

void SecondEvent::create_window()
{
    if(windows.size() >= MAX_WINDOWS) return;
    
    auto w = new MovingWindow({200, 50}, ">:)", sf::Style::Close);
    if(second_phase)
    {
        w->velocity = rand_vec2(sf::Vector2f(-1, -1), sf::Vector2f(1, 1));
        w->velocity /= sqrt(square(w->velocity.x) + square(w->velocity.y));
        w->velocity *= rand_range(50.f, 300.f);
    }
    windows.push_back(w);
    w->setPosition(rand_vec2(sf::Vector2i(0, 0),
                                          sf::Vector2i(
                                              sf::VideoMode::getDesktopMode().width - w->getSize().x,
                                              sf::VideoMode::getDesktopMode().height - w->getSize().y - 100
                                              )));

    w->background_color = rand_color();
    w->on_request_close.bind(this, &SecondEvent::on_window_closed);

    const auto t = new TextWidget;
    t->setString(possible_texts[rand() % possible_texts.size()]);
    t->setFillColor(rand_color());
    t->setOutlineColor(rand_color());
    t->setOutlineThickness(1);
    t->add_to_parent(w);
    t->local_transform.translate(static_cast<sf::Vector2f>(w->getSize()) / 2.f);
    centre_drawable(t);
    
    t->setFont(FontManager::get_font_by_name(font_names[rand() % font_names.size()]));
}

void SecondEvent::start_second_phase()
{
    second_phase = true;
    for(int i = 0; i < MAX_WINDOWS; i++)
        create_window();
}

void SecondEvent::transition()
{
    if(second_phase)
    {
        end_internal();
        return;
    }
    transition_window = new WindowManager({520, 50}, "Enjoying yourself?", sf::Style::Close);
    const auto txt = new TextWidget;
    txt->setString("Too easy? Let me \"move\" things up a notch...");
    txt->local_transform.translate(static_cast<sf::Vector2f>(transition_window->getSize()) / 2.f);
    centre_drawable(txt);
    txt->add_to_parent(transition_window);

    transition_window->on_request_close.bind(this, &SecondEvent::start_second_phase);
}

void SecondEvent::on_window_closed()
{
    for(size_t i = 0; i < windows.size(); i++)
    {
        if(windows[i]->isOpen()) continue;

        windows[i]->mark_for_deletion();
        windows.erase(windows.begin() + static_cast<long long>(i));
        i--;
    }
    if(windows.size() <= 1)
        running = false;

    if(windows.empty())
        Timer::create_timer_by_function(this, &SecondEvent::transition, 3, false);
}
