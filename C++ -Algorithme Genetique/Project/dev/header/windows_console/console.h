//
//
//
// Un exemple simple :
// 
// using namespace windows_console;
// 
// cout << "Press any key to continue...";
//
// csl << press_any_key_to_continue;
// csl << clear;
//
// csl  << window::title("My application title")
//      << window::fit(300, 150, "Consolas", 3, 3)
//      << window::unresizable
//      << window::unclosable
//      << window::center
//      << cursor::invisible;
//
//
// image im;
// csl >> im;
//
// im   << brush(dot, text_color(dark, blue), background_color(dark, blue)) << fill;
//
// im   << pen(dot, text_color(bright, blue), background_color(bright, blue)) 
//      << point(50, 25))
//      << line(0, 0, 100, 100))
//      << circle(100, 100, 25));
//
// im   << no_brush
//      << rectangle(12, 21, 43, 34);
//      
// csl << im;
//
// while (!quit) {
//      console_events consoleEvents;
//      consoleEvents.read_events();
//      while (consoleEvents.key_events_count() > 0) {
//           key_event e{ consoleEvents.next_key_event() };
//           switch (consoleEvents.next_key_event().ascii_value()) {
//               case 'a':
//               case 'A':
//                   goLeft();
//                   break;
//               case 'd':
//               case 'D':
//                   goRight();
//                   break;
//               case 27 : // escape
//                   quit = true;
//                   break;
//           }
//      }
// }
//
//
//
// considérations :
//  - le brightness n'a aucun impact sur la couleur noire (autant pour le texte que pour le background)
// - faire un '\n' (ou endl) colore le background de la nouvelle ligne complètement selon la couleur de background 
//
//
// problèmes :
// - changement de dpi ou de résolution d'écran, la proportionalité de la taille de police change et revient à la proportion standardisée
//
//


#pragma once
#ifndef _WINDOWS_CONSOLE_H_
#define _WINDOWS_CONSOLE_H_

#pragma warning( disable : 4624 ) // destructor was implicitly defined as deleted

#include <type_traits>
#include <functional>
#include <memory>

#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>

#include <utility>
#include <algorithm>

#include <exception>
#include <cassert>

namespace windows_console
{

    namespace detail // internal private Hidden namespace
    {
        //                                             _                   _   _ _     _      
        //    _ __   ___  _ __      ___ ___  _ __  ___| |_ _ __ _   _  ___| |_(_) |__ | | ___ 
        //   | '_ \ / _ \| '_ \    / __/ _ \| '_ \/ __| __| '__| | | |/ __| __| | '_ \| |/ _ \
        //   | | | | (_) | | | |  | (_| (_) | | | \__ \ |_| |  | |_| | (__| |_| | |_) | |  __/
        //   |_| |_|\___/|_| |_|___\___\___/|_| |_|___/\__|_|   \__,_|\___|\__|_|_.__/|_|\___|
        //                    |_____|                                                         
        class non_constructible {
        public:
            non_constructible() = delete;
            non_constructible(non_constructible const &) = delete;
            non_constructible(non_constructible &&) = delete;
            ~non_constructible() = delete;
            non_constructible& operator=(non_constructible const &) = delete;
            non_constructible& operator=(non_constructible &&) = delete;
        };

        //                                                     _     _      
        //    _ __   ___  _ __      ___ ___  _ __  _   _  __ _| |__ | | ___ 
        //   | '_ \ / _ \| '_ \    / __/ _ \| '_ \| | | |/ _` | '_ \| |/ _ \
        //   | | | | (_) | | | |  | (_| (_) | |_) | |_| | (_| | |_) | |  __/
        //   |_| |_|\___/|_| |_|___\___\___/| .__/ \__, |\__,_|_.__/|_|\___|
        //                    |_____|       |_|    |___/                    
        class non_copyable {
        public:
            non_copyable() = default;
            non_copyable(non_copyable const &) = delete;
            non_copyable(non_copyable &&) = delete;
            ~non_copyable() = default;
            non_copyable& operator=(non_copyable const &) = delete;
            non_copyable& operator=(non_copyable &&) = delete;
        };

        //                              _                                _          _         _             _ _   
        //     ___ ___  _ __  ___  ___ | | ___     _ __ ___   __ _ _ __ (_)_ __    (_) ___   | |_ _ __ __ _(_) |_ 
        //    / __/ _ \| '_ \/ __|/ _ \| |/ _ \   | '_ ` _ \ / _` | '_ \| | '_ \   | |/ _ \  | __| '__/ _` | | __|
        //   | (_| (_) | | | \__ \ (_) | |  __/   | | | | | | (_| | | | | | |_) |  | | (_) | | |_| | | (_| | | |_ 
        //    \___\___/|_| |_|___/\___/|_|\___|___|_| |_| |_|\__,_|_| |_|_| .__/___|_|\___/___\__|_|  \__,_|_|\__|
        //                                   |_____|                      |_| |_____|    |_____|                  
        template <typename t>
        class console_manip_io_trait
        {
        private:
            struct fallback_insert { struct insert {}; };
            struct derived_insert : t, fallback_insert { };
            struct fallback_extract { struct extract {}; };
            struct derived_extract : t, fallback_extract { };

            template <typename u> static constexpr std::false_type test_insert(typename u::insert*);
            template <typename u> static constexpr std::true_type test_insert(u*);
            template <typename u> static constexpr std::false_type test_extract(typename u::extract*);
            template <typename u> static constexpr std::true_type test_extract(u*);

        public:
            static constexpr bool insertion_enabled = std::is_same_v<std::true_type, decltype(test_insert<derived_insert>(nullptr))>;
            static constexpr bool extraction_enabled = std::is_same_v<std::true_type, decltype(test_extract<derived_extract>(nullptr))>;
        };

        //    _                                                 _                                _       
        //   | |__   __ _ ___  ___     ___ ___  _ __  ___  ___ | | ___     _ __ ___   __ _ _ __ (_)_ __  
        //   | '_ \ / _` / __|/ _ \   / __/ _ \| '_ \/ __|/ _ \| |/ _ \   | '_ ` _ \ / _` | '_ \| | '_ \ 
        //   | |_) | (_| \__ \  __/  | (_| (_) | | | \__ \ (_) | |  __/   | | | | | | (_| | | | | | |_) |
        //   |_.__/ \__,_|___/\___|___\___\___/|_| |_|___/\___/|_|\___|___|_| |_| |_|\__,_|_| |_|_| .__/ 
        //                       |_____|                             |_____|                      |_|    
        template <typename t>
        class base_console_manip //: public non_copyable
        {
        public:
            static constexpr bool insertion_enabled() { return console_manip_io_trait<t>::insertion_enabled; }
            static constexpr bool extraction_enabled() { return console_manip_io_trait<t>::extraction_enabled; }

            template <typename = std::enable_if<insertion_enabled(), int>::type> void do_insert() { static_cast<t*>(this)->insert(); }
            template <typename = std::enable_if<extraction_enabled(), int>::type> void do_extract() { static_cast<t*>(this)->extract(); }
        };

        //                          _ 
        //     ___  _ __ ___  _ __ (_)
        //    / _ \| '_ ` _ \| '_ \| |
        //   | (_) | | | | | | | | | |
        //    \___/|_| |_| |_|_| |_|_|
        //                            
        // very naive implementation... to redo...
        template <typename T>
        class omni
        {
        public:
            using value_type = T;
            enum class access_mode : int8_t { invalid = 0, instance, pointer, reference };

        private:
            T _value;
            T * _ref; // if _ref !nullptr => always use _ref, else use _value
            access_mode _access_mode;

            void validate() const { if (_access_mode == access_mode::invalid) throw(std::exception("bad omni")); }

        public:
            omni() : _value{}, _ref{}, _access_mode{ access_mode::invalid } {}
            omni(T const & v) : _value(v), _ref{}, _access_mode{ access_mode::instance } {}
            explicit omni(T & v) : _value(), _ref{ &v }, _access_mode{ access_mode::pointer } {}
            explicit omni(T * v) : _value(), _ref{ v }, _access_mode{ access_mode::reference } {}

            //operator bool() const { return _access_mode != access_mode::invalid; } // conflict with conversion to internal bool type
            operator T&() { validate(); return _ref ? *_ref : _value; }
            operator T const &() const { validate(); return _ref ? *_ref : _value; }

            T& operator()() { validate(); return _ref ? *_ref : _value; }
            T const & operator()() const { validate(); return _ref ? *_ref : _value; }

            omni<T>& operator=(omni<T> const & v) { if (_ref) *_ref = static_cast<T>(v); else _value = static_cast<T>(v); return *this; }
            omni<T>& operator=(T const & v) { if (_ref) *_ref = v; else _value = v; return *this; }

            access_mode current_access_mode() const { return _ref ? mode_type::reference : mode_type::instance; }
            bool is_valid() const { return static_cast<bool>(_access_mode); }
        };
    }

    //                              _      
    //     ___ ___  _ __  ___  ___ | | ___ 
    //    / __/ _ \| '_ \/ __|/ _ \| |/ _ \
    //   | (_| (_) | | | \__ \ (_) | |  __/
    //    \___\___/|_| |_|___/\___/|_|\___|
    //                                     
    class console
    {
    private:
        console() = default;
        console(console const &) = delete;
        console(console &&) = delete;
        console& operator=(console const &) = delete;
        console& operator=(console &&) = delete;
        ~console() = default;

    public:
        static console & instance();
    };

    //             _ 
    //     ___ ___| |
    //    / __/ __| |
    //   | (__\__ \ |
    //    \___|___/_|
    //               
    inline console & csl{ console::instance() };

    //                              _                                 _   _             
    //     ___ ___  _ __  ___  ___ | | ___     _____  _____ ___ _ __ | |_(_) ___  _ __  
    //    / __/ _ \| '_ \/ __|/ _ \| |/ _ \   / _ \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \ 
    //   | (_| (_) | | | \__ \ (_) | |  __/  |  __/>  < (_|  __/ |_) | |_| | (_) | | | |
    //    \___\___/|_| |_|___/\___/|_|\___|___\___/_/\_\___\___| .__/ \__|_|\___/|_| |_|
    //                                   |_____|               |_|                      
    class console_exception : public std::exception
    {
    private:
        std::string _err_msg;
        void build_msg(std::string const & context, std::string const & user_info = std::string(), bool include_last_error_console = true, bool include_last_error_message = true);

    public:
        console_exception(std::string const & context, std::string const & user_info = std::string(), bool include_last_error_console = true, bool include_last_error_message = true);
        console_exception(console_exception const &) = default;
        console_exception(console_exception &&) = default;
        ~console_exception() = default;
        console_exception& operator=(console_exception const &) = default;
        console_exception& operator=(console_exception &&) = default;

        [[nodiscard]] char const * what() const noexcept override;
    };



    //! \brief Classe manipulant les pages de code de l'entrée et de la sortie.
    //!
    //! \detail Cette classe possède plusieurs outils permettant la manipulation des pages de code de la console. 
    //! 
    //! Une page de code est un standard informatique qui vise à donner un numéro à chaque caractère d'une langue 
    //! (<a href="https://fr.wikipedia.org/wiki/Page_de_code">Wikipedia</a>). Par exemple, voici quelques pages de 
    //! code fréquemment utilisées en Amérique du nord :
    //!  - 850 : alphabet latin latin (langues d'Europe occidentale) utilisé par le système d'exploitation DOS
    //!  - 1252 : alphabet latin latin (langues d'Europe occidentale) utilisé par le système d'exploitation Windows
    //!  - 65000 : Unicode (UTF-7)
    //!  - 65001 : Unicode (UTF-8)
    //! 
    //! Une page de code est représentée par :
    //!  - un nombre
    //!  - un nom
    //!
    //! D'abord, deux sous classes s'occupent des manipulations spécifiques liées aux entrées et à la sortie :
    //!  - code_page::input
    //!  - code_page::output
    //! 
    //! Certaines fonctions utilistaires permettent d'obtenir des informations sur les pages de codes disponibles :
    //!  - dictionary : la liste des pages de codes disponibles
    //!  - is_available : valider si une page de code est disponible
    //!  - name_of : retrouver le nom d'une page de code à partir du code 
    class code_page : public detail::non_constructible
    {
    public:
        using number_type = uint32_t;                                                   //!< type des nombres
        using name_type = std::string;                                                  //!< type des noms
        using dictionary_type = std::map<number_type, name_type>;                       //!< type du dictionnaire où se trouve les pages de code disponibles

        class input;                                                                    //!< type manipulant les pages de code en entrée
        class output;                                                                   //!< type manipulant les pages de code en sortie

        [[nodiscard]] static dictionary_type const & dictionary();                      //!< retourne le dictionnaire de toutes les pages de code disponibles
        [[nodiscard]] static bool is_available(number_type number);                     //!< détermine si une page de code est disponible
        [[nodiscard]] static std::string const & name_of(number_type number);           //!< retourne le nom d'une page de code (si le code n'est pas disponible, retourne la chaîne de caractères not_available_name)

        [[nodiscard]] static std::string const & not_available_name();                  //!< retourne la chaîne de caractères retournée par la fonction name_of lorsqu'une page de code n'est pas disponible

    private:
        static name_type const _not_available_name;
        static dictionary_type const _dictionary;
        static dictionary_type build_dictionary();
    };

    //! \brief Classe manipulant la page de code (*code page*) de l'entrée (clavier).
    //!
    //! \detail Cette classe permet :
    //!     - l'extraction du :
    //!         - code de la page de code utilisée par l'entrée
    //!         - nom de la page de code utilisée par l'entrée
    //!     - la modification de :
    //!         - la page de code utilisée par l'entrée
    //!
    //! \code{.cpp}
    //! code_page::number_type number;
    //! code_page::name_type name;
    //! csl >> code_page::input(number, name);      // extraction of code page information (number and name)
    //! csl << code_page::input(1252);              // modification of code page by number
    //! \endcode
    class code_page::input : public detail::base_console_manip<input>
    {
    public:
        input(number_type const & c);
        explicit input(number_type & c);
        explicit input(number_type & c, name_type & n);

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        detail::omni<number_type> _code;
        detail::omni<name_type> _name;
    };

    //! \brief Classe manipulant la page de code (*code page*) de la sortie (écran).
    //!
    //! \detail Cette classe permet :
    //!     - l'extraction du :
    //!         - nombre de la page de code utilisée par la sortie
    //!         - nom de la page de code utilisée par la sortie
    //!     - la modification de :
    //!         - la page de code utilisée par la sortie
    //! 
    //! [check]: check.png ""
    //! [cross]: cross.png ""
    //! 
    //! | Opération                 | Extraction            | Modification          | Type                    |
    //! | :------------------------ | :-------------------: | :-------------------: | :---------------------- |
    //! | Nombre de la page de code | ![][check]            | ![][check]            | code_page::name_type |
    //! | Nom de la page de code    | ![][check]            | ![][cross]            | code_page::name_type    |
    //! 
    //! ![][check]
    //! ![][check]
    //! ![][check]
    //! 
    //! <table>
    //! <caption>code_page::output</caption>
    //! <tr><th> Opération                  <th> Extraction             <th> Modification           <th> Type
    //! <tr><td> Nombre de la page de code  <td> <img src="check.png">     <td> <img src="check.png">             <td> code_page::name_type
    //! 
    //! 
    //! 
    //! </table>
    //! 
    //! 
    //! 
    //! \code{.cpp}
    //! code_page::number_type number;
    //! code_page::name_type name;
    //! csl >> code_page::output(number, name);      // extraction of code page information (number and name)
    //! csl << code_page::output(1252);              // modification of code page by number
    //! \endcode
    class code_page::output : public detail::base_console_manip<output>
    {
    public:
        output(number_type const & c);
        explicit output(number_type & c);
        explicit output(number_type & c, name_type & n);

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        detail::omni<number_type> _code;
        detail::omni<name_type> _name;
    };

    //! \brief Classe manipulant certaines informations sur la fenêtre liée à la console.
    //!
    //! \detail Cette classe permet :
    //!     - l'extraction du :
    //!         - code de la page de code utilisée par la sortie
    //!         - nom de la page de code utilisée par la sortie
    //!     - la modification de :
    //!         - la page de code utilisée par la sortie
    //!
    //! \code{.cpp}
    //! code_page::number_type number;
    //! code_page::name_type name;
    //! csl >> code_page::output(number, name);      // extraction of code page information (number and name)
    //! csl << code_page::output(1252);              // modification of code page by number
    //! \endcode
    class window
    {
    public:
        class title;
        //class icon;

        class fit;

        static console& center(console & c);
        static console& unresizable(console & c);
        //static console& resizable(console & c);... to do
        static console& unclosable(console & c);
        //static console& closable(console & c);... to do
    };


    console& clear(console & c); // to redo
    console& press_any_key_to_continue(console & c); // to redo



    //             _           _                   _   _ _   _      
    //   __      _(_)_ __   __| | _____      ___ _| |_(_) |_| | ___ 
    //   \ \ /\ / / | '_ \ / _` |/ _ \ \ /\ / (_|_) __| | __| |/ _ \
    //    \ V  V /| | | | | (_| | (_) \ V  V / _ _| |_| | |_| |  __/
    //     \_/\_/ |_|_| |_|\__,_|\___/ \_/\_/ (_|_)\__|_|\__|_|\___|
    //                                                                         
    class window::title : public detail::base_console_manip<title>
    {
    public:
        using name_type = std::string;

        title(name_type const & t) : _title(t) {}
        explicit title(name_type & t) : _title(t) {}

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        detail::omni<name_type> _title;
    };

    //             _           _                   _                 
    //   __      _(_)_ __   __| | _____      ___ _(_) ___ ___  _ __  
    //   \ \ /\ / / | '_ \ / _` |/ _ \ \ /\ / (_|_) |/ __/ _ \| '_ \ 
    //    \ V  V /| | | | | (_| | (_) \ V  V / _ _| | (_| (_) | | | |
    //     \_/\_/ |_|_| |_|\__,_|\___/ \_/\_/ (_|_)_|\___\___/|_| |_|
    //                                                                
    // class window::icon {}; ... to do


    //        _                 
    //    ___| | ___  ___ _ __  
    //   / __| |/ _ \/ _ \ '_ \ 
    //   \__ \ |  __/  __/ |_) |
    //   |___/_|\___|\___| .__/ 
    //                   |_|    
    class sleep : public detail::base_console_manip<sleep>
    {
    public:
        using time_type = double;

        sleep(time_type const & time_in_second) : _time(time_in_second) {}

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        //void extract();

        detail::omni<time_type> _time;
    };


    //     __             _   
    //    / _| ___  _ __ | |_ 
    //   | |_ / _ \| '_ \| __|
    //   |  _| (_) | | | | |_ 
    //   |_|  \___/|_| |_|\__|
    //                        
    // font
    //
    // write :
    //      font(name)                                              csl << font("arial");                       
    //      font(weight)                                            csl << font(font::weight_t::bold);
    //      font(height)                                            csl << font(12);
    //      font(height, ratio)                                     csl << font(12, 0.5);
    //      font(width, height)                                     csl << font(12, 16);
    //      font(name, weight)                                      csl << font("courrier new", percent_080);
    //      font(name, height)                                      csl << font("consolas", 20);
    //      font(name, height, ratio)                               csl << font("consolas", 20, 0.75);
    //      font(name, weight, height)                              csl << font("calibri", font::weight_t::light, 10)
    //      font(name, weight, height, ratio)                       csl << font("calibri", font::weight_t::light, 10, 1.0); 
    //      font(name, width, height)                               csl << font("arial", 20, 30);
    //      font(name, weight, width, height)                       csl << font("arial", font::weight_t::heavy_bold, 5, 5);
    //
    //      font::thin                                              csl << font::thin;
    //      font::normal                                            csl << font::normal;
    //      font::bold                                              csl << font::bold;
    //      font::heavy_bold                                        csl << font::heavy_bold;
    //
    // read :
    //      font(name)                                              std::string actual_font_name;                   csl >> font(actual_font_name);
    //      font(weight)                                            font::weight_t actual_font_weight;              csl >> font(actual_font_weight);
    //      font(width, height)                                     int32_t actual_font_width, actual_font_height;  csl >> font(actual_font_width, actual_font_height);
    //      font(name, weight)                                                                                      csl >> font(actual_font_name, actual_font_weight);
    //      font(name, width, height)                                                                               csl >> font(actual_font_name, actual_font_width, actual_font_height);
    //      font(name, weight, width, height)                                                                       csl >> font(actual_font_name, actual_font_weight, actual_font_width, actual_font_height);
    //
    // types specification :
    //      - name              std::string
    //      - weight            font::weight
    //      - height            int32_t
    //      - width             int32_t
    //      - ratio             double                  ratio is used when width is relative to height (no width is specified) 
    //                                                  if ratio = 0, the font used automatic proportional scale
    //                                                  if ratio = 1, the font is square
    //
    // example :
    //      std::string font_name;
    //
    //      csl >> font(font_name);     // font_name = the font name currently used by the console
    //      csl << font("arial");       // set a new font
    //      csl >> font(font_name);     // font_name = the font name currently used by the console
    //      
    //      csl << font("Consolas", font::weight::bold, 8, 0.0);    
    //      csl << font::normal;
    // 
    class font : public detail::base_console_manip<font>
    {
    public:
        using size_type = uint32_t;
        using ratio_type = double;
        using name_type = std::string;

        enum class weight_type : uint32_t {
            percent_010 = 100,
            percent_020 = 200,
            percent_030 = 300,
            percent_040 = 400,
            percent_050 = 500,
            percent_060 = 600,
            percent_070 = 700,
            percent_080 = 800,
            percent_090 = 900,
            percent_100 = 1000,
            thin = percent_020,
            normal = percent_040,
            bold = percent_070,
            heavy_bold = percent_090
        };

        font(name_type const & name) : _width(), _height(), _ratio(), _weight(), _name(name), _size_mode{ none } {}
        font(weight_type const & weight) : _width(), _height(), _ratio(), _weight(weight), _name(), _size_mode{ none } {}
        font(size_type const & height, ratio_type const & ratio = 0.0) : _width(), _height(height), _ratio(ratio), _weight(), _name(), _size_mode{ relative } {}
        font(size_type const & width, size_type const & height) : _width(width), _height(height), _ratio(), _weight(), _name(), _size_mode{ absolute } {}
        font(name_type const & name, weight_type const & weight) : _width(), _height(), _ratio(), _weight(weight), _name(name), _size_mode{ none } {}
        font(name_type const & name, size_type const & height, ratio_type const & ratio = 0.0) : _width(), _height(height), _ratio(ratio), _weight(), _name(name), _size_mode{ relative } {}
        font(name_type const & name, weight_type const & weight, size_type const & height, ratio_type const & ratio = 0.0) : _width(), _height(height), _ratio(ratio), _weight(weight), _name(name), _size_mode{ relative } {}
        font(name_type const & name, size_type const & width, size_type const & height) : _width(width), _height(height), _ratio(), _weight(), _name(name), _size_mode{ absolute } {}
        font(name_type const & name, weight_type const & weight, size_type const & width, size_type const & height) : _width(width), _height(height), _ratio(), _weight(weight), _name(name), _size_mode{ absolute } {}

        explicit font(name_type & name) : _width(), _height(), _ratio(), _weight(), _name(name), _size_mode{} {}
        explicit font(weight_type & weight) : _width(), _height(), _ratio(), _weight(weight), _name(), _size_mode{} {}
        explicit font(size_type & width, size_type & height) : _width(width), _height(height), _ratio(), _weight(), _name(), _size_mode{} {}
        explicit font(name_type & name, weight_type & weight) : _width(), _height(), _ratio(), _weight(weight), _name(name), _size_mode{} {}
        explicit font(name_type & name, size_type & width, size_type & height) : _width(width), _height(height), _ratio(), _weight(), _name(name), _size_mode{} {}
        explicit font(name_type & name, weight_type & weight, size_type & width, size_type & height) : _width(width), _height(height), _ratio(), _weight(weight), _name(name), _size_mode{} {}

        static console& thin(console & c);
        static console& normal(console & c);
        static console& bold(console & c);
        static console& heavy_bold(console & c);


    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        detail::omni<size_type> _width;
        detail::omni<size_type> _height;
        detail::omni<ratio_type> _ratio;
        detail::omni<weight_type> _weight;
        detail::omni<name_type> _name;

        enum size_mode { none = 0, absolute, relative } _size_mode;
    };


    //    _            __  __           
    //   | |__  _   _ / _|/ _| ___ _ __ 
    //   | '_ \| | | | |_| |_ / _ \ '__|
    //   | |_) | |_| |  _|  _|  __/ |   
    //   |_.__/ \__,_|_| |_|  \___|_|   
    //                                  
    // this class must be extended to it's full potential
    class buffer : public detail::base_console_manip<buffer>
    {
    public:
        using size_type = uint32_t;

        explicit buffer(size_type & width, size_type & height) : _width(width), _height(height) {}

    private:
        template <typename t> friend class detail::base_console_manip;
        //void insert();
        void extract();

        detail::omni<size_type> _width;
        detail::omni<size_type> _height;
    };


    //     __ _ _   
    //    / _(_) |_ 
    //   | |_| | __|
    //   |  _| | |_ 
    //   |_| |_|\__|
    //              
    class window::fit : public detail::base_console_manip<fit>
    {
    public:
        using size_type = uint32_t;

        fit(size_type const & screen_width, size_type const & screen_height, font::name_type const & font_name, font::size_type const & font_width, font::size_type const & font_height) : _screen_width(screen_width), _screen_height(screen_height), _font_width(font_width), _font_height(font_height), _font_name(font_name), _font_ratio() {}
        fit(size_type const & screen_width, size_type const & screen_height, font::name_type const & font_name, font::size_type const & font_height, font::ratio_type const & font_ratio) : _screen_width(screen_width), _screen_height(screen_height), _font_width(), _font_height(font_height), _font_name(font_name), _font_ratio(font_ratio) {}

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        //void extract();

        detail::omni<size_type> _screen_width;
        detail::omni<size_type> _screen_height;
        detail::omni<font::name_type> _font_name;
        detail::omni<font::size_type> _font_width;
        detail::omni<font::size_type> _font_height;
        detail::omni<font::ratio_type> _font_ratio;
    };

    //                                   
    //     ___ _   _ _ __ ___  ___  _ __ 
    //    / __| | | | '__/ __|/ _ \| '__|
    //   | (__| |_| | |  \__ \ (_) | |   
    //    \___|\__,_|_|  |___/\___/|_|   
    //                                   
    class cursor : public detail::base_console_manip<cursor>
    {
    public:
        using size_type = size_t;

        cursor(size_type const & size) : _size(std::clamp(size, size_type{}, size_type{ 100 })), _visible() {}
        cursor(bool const & visible) : _size(), _visible(visible) {}
        cursor(bool const & visible, size_type const & size) : _size(std::clamp(size, size_type{}, size_type{ 100 })), _visible(visible) {}

        explicit cursor(size_type & size) : _size(size), _visible() {}
        explicit cursor(bool & visible) : _size(), _visible(visible) {}
        explicit cursor(bool & visible, size_type & size) : _size(size), _visible(visible) {}

        static console& visible(console & c);
        static console& invisible(console & c);

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        detail::omni<size_type> _size;
        detail::omni<bool> _visible;
    };

    //                    _ _   _             
    //    _ __   ___  ___(_) |_(_) ___  _ __  
    //   | '_ \ / _ \/ __| | __| |/ _ \| '_ \ 
    //   | |_) | (_) \__ \ | |_| | (_) | | | |
    //   | .__/ \___/|___/_|\__|_|\___/|_| |_|
    //   |_|                                  
    class position : public detail::base_console_manip<position>
    {
    public:
        using coordinate_type = uint32_t;

        position(coordinate_type const & x, coordinate_type const & y) : _x(x), _y(y) {}
        position(coordinate_type & x, coordinate_type & y) : _x(x), _y(y) {}

        static console& push(console & c);
        static console& pop(console & c);
        static console& clear(console & c);

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        using coord_t = struct { coordinate_type x, y; };
        using stack_t = std::stack<coord_t>;

        static stack_t _stack;

        detail::omni<coordinate_type> _x;
        detail::omni<coordinate_type> _y;
    };


    //                                                                                                                                                                                   
    //    _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____  
    //   |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| 
    //                                                                                                                                                                                   
    //                                                                                                                                                                                   


    //              _            _                    
    //     ___ ___ | | ___  _ __| |_ _   _ _ __   ___ 
    //    / __/ _ \| |/ _ \| '__| __| | | | '_ \ / _ \
    //   | (_| (_) | | (_) | |  | |_| |_| | |_) |  __/
    //    \___\___/|_|\___/|_|___\__|\__, | .__/ \___|
    //                      |_____|  |___/|_|         
    enum color_type { black = 0, red = 4, green = 2, blue = 1, yellow = 6, cyan = 3, magenta = 5, white = 7 };

    //    _          _       _     _                          _                    
    //   | |__  _ __(_) __ _| |__ | |_ _ __   ___  ___ ___   | |_ _   _ _ __   ___ 
    //   | '_ \| '__| |/ _` | '_ \| __| '_ \ / _ \/ __/ __|  | __| | | | '_ \ / _ \
    //   | |_) | |  | | (_| | | | | |_| | | |  __/\__ \__ \  | |_| |_| | |_) |  __/
    //   |_.__/|_|  |_|\__, |_| |_|\__|_| |_|\___||___/___/___\__|\__, | .__/ \___|
    //                 |___/                             |_____|  |___/|_|         
    enum brightness_type { dark = 0, bright = 1 };

    namespace detail {
        using attribute_type = uint16_t;

        attribute_type attribute(int offset, color_type c, brightness_type b);
        void hue_brightness(int offset, attribute_type a, color_type & c, brightness_type & b);
        //attribute_type attribute_omni(int offset, omni<color_type> const & c, omni<brightness_type> const & b);
        //void hue_brightness_omni(int offset, attribute_type a, omni<color_type> & c, omni<brightness_type> & b);
        void color_management_insertion(int offset, omni<color_type> const & c, omni<brightness_type> const & b);
        void color_management_extraction(int offset, omni<color_type> & c, omni<brightness_type> & b);
        void toggle_brightness(int offset);
        void cycle_hue(int offset, bool next);

    }

    //              _                                                                         _   
    //     ___ ___ | | ___  _ __  _ __ ___   __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_ 
    //    / __/ _ \| |/ _ \| '__|| '_ ` _ \ / _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|
    //   | (_| (_) | | (_) | |   | | | | | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ 
    //    \___\___/|_|\___/|_|___|_| |_| |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|
    //                      |_____|                           |___/                               
    template <bool lower4>
    class color_management : public detail::base_console_manip<color_management<lower4>>
    {
    public:
        color_management(color_type const & color) : _color(color), _brightness() {}
        color_management(brightness_type const & brightness) : _color(), _brightness(brightness) {}
        color_management(brightness_type const & brightness, color_type const & color) : _color(color), _brightness(brightness) {}

        explicit color_management(color_type & color) : _color(color), _brightness() {}
        explicit color_management(brightness_type & brightness) : _color(), _brightness(brightness) {}
        explicit color_management(brightness_type & brightness, color_type & color) : _color(color), _brightness(brightness) {}

        static console& toggle_brightness(console & c) { detail::toggle_brightness(_offset); return c; }
        static console& cycle_hue(console & c) { detail::cycle_hue(_offset, true); return c; }
        static console& reverse_cycle_hue(console & c) { detail::cycle_hue(_offset, false); return c; }

    private:
        template <typename t> friend class detail::base_console_manip;
        void insert() { detail::color_management_insertion(_offset, _color, _brightness); }
        void extract() { detail::color_management_extraction(_offset, _color, _brightness); }

        detail::omni<color_type> _color;
        detail::omni<brightness_type> _brightness;

        static constexpr int _offset{ static_cast<int>(lower4) * 4 };

        friend class pen;
        friend class brush;
    };

    //    _            _                _            
    //   | |_ _____  _| |_     ___ ___ | | ___  _ __ 
    //   | __/ _ \ \/ / __|   / __/ _ \| |/ _ \| '__|
    //   | ||  __/>  <| |_   | (_| (_) | | (_) | |   
    //    \__\___/_/\_\\__|___\___\___/|_|\___/|_|   
    //                   |_____|                     
    using text_color = color_management<false>;

    //    _                _                                   _              _            
    //   | |__   __ _  ___| | ____ _ _ __ ___  _   _ _ __   __| |    ___ ___ | | ___  _ __ 
    //   | '_ \ / _` |/ __| |/ / _` | '__/ _ \| | | | '_ \ / _` |   / __/ _ \| |/ _ \| '__|
    //   | |_) | (_| | (__|   < (_| | | | (_) | |_| | | | | (_| |  | (_| (_) | | (_) | |   
    //   |_.__/ \__,_|\___|_|\_\__, |_|  \___/ \__,_|_| |_|\__,_|___\___\___/|_|\___/|_|   
    //                         |___/                           |_____|                     
    using background_color = color_management<true>;

    //using txt_col = text_color;
    //using bg_col = background_color;



    //        _       _   
    //     __| | ___ | |_ 
    //    / _` |/ _ \| __|
    //   | (_| | (_) | |_ 
    //    \__,_|\___/ \__|
    //                    
    inline static constexpr char dot{ (char)219 };


    //    _                            
    //   (_)_ __ ___   __ _  __ _  ___ 
    //   | | '_ ` _ \ / _` |/ _` |/ _ \
    //   | | | | | | | (_| | (_| |  __/
    //   |_|_| |_| |_|\__,_|\__, |\___|
    //                      |___/      
    class image_manipulator;

    class image : public detail::base_console_manip<image>
    {
    public:
        using size_type = uint32_t;

        image();
        image(image const &) = default;
        image(image &&) = default;
        image& operator=(image const &) = default;
        image& operator=(image &&) = default;
        ~image() = default;

        bool is_valid() const;
        size_type width() const { return _width; }
        size_type height() const { return _height; }

        // image& operator>>(image & other);        // to do ...
        // image& operator<<(image & other);        // to do ...

    private:
        struct pixel_type {
            union {
                wchar_t unicode_char;
                char   ascii_char;
            } char_value;
            uint16_t attributes;
            explicit pixel_type(char c = dot, uint16_t a = 0) { char_value.ascii_char = c; attributes = a; }
        };

        template <typename t> friend class detail::base_console_manip;
        void insert();
        void extract();

        size_type _width, _height, _buffer_size;
        std::vector<pixel_type> _buffer;
        bool _use_pen;
        bool _use_brush;
        pixel_type _pen;
        pixel_type _brush;

        pixel_type const & pixel(int x, int y);
        void set_pixel(int x, int y, pixel_type const & p);
        void draw_point(int x, int y, pixel_type const & p);
        void draw_line(int x1, int y1, int x2, int y2, pixel_type const & p);
        void draw_hline(int x, int y, int length, pixel_type const & p);
        void draw_vline(int x, int y, int length, pixel_type const & p);

        void fill(pixel_type const & p);
        void swap_pen_brush();
        void randomize();

        friend image & no_pen(image &);
        friend image & no_brush(image &);
        friend image & fill(image &);
        friend image & swap_pen_brush(image &);
        friend image & randomize(image &);
        friend class pen;
        friend class brush;
        friend class point;
        friend class line;
        friend class hline;
        friend class vline;
        friend class rectangle;
        friend class circle;
    };

    image & no_pen(image & i);
    image & no_brush(image & i);
    image & fill(image & i);
    image & swap_pen_brush(image & i);
    image & randomize(image & i);


    //    _                                                      _             _       _             
    //   (_)_ __ ___   __ _  __ _  ___     _ __ ___   __ _ _ __ (_)_ __  _   _| | __ _| |_ ___  _ __ 
    //   | | '_ ` _ \ / _` |/ _` |/ _ \   | '_ ` _ \ / _` | '_ \| | '_ \| | | | |/ _` | __/ _ \| '__|
    //   | | | | | | | (_| | (_| |  __/   | | | | | | (_| | | | | | |_) | |_| | | (_| | || (_) | |   
    //   |_|_| |_| |_|\__,_|\__, |\___|___|_| |_| |_|\__,_|_| |_|_| .__/ \__,_|_|\__,_|\__\___/|_|   
    //                      |___/    |_____|                      |_|                                
    class image_manipulator;
}

windows_console::image& operator<<(windows_console::image & i, windows_console::image_manipulator & m);
windows_console::image& operator<<(windows_console::image & i, windows_console::image_manipulator && m);

namespace windows_console {
    class image_manipulator
    {
    public:
        using coordinate_type = int32_t;

    protected:
        virtual void manip(image & i) = 0;

        friend windows_console::image& ::operator<<(image & i, image_manipulator & m);
        friend windows_console::image& ::operator<<(image & i, image_manipulator && m);
    };

    class pen : public image_manipulator
    {
    public:
        pen(char c, text_color const & tc, background_color const & bc);

    protected:
        void manip(image & i) override;
        
    private:
        char _char;
        text_color _text_color;
        background_color _background_color;
    };

    class brush : public image_manipulator
    {
    public:
        brush(char c, text_color const & tc, background_color const & bc);

    protected:
        void manip(image & i) override;

    private:
        char _char;
        text_color _text_color;
        background_color _background_color;
    };

    class point : public image_manipulator
    {
    public:
        point(coordinate_type x, coordinate_type y) : _x{ x }, _y{ y } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x, _y;
    };

    class line : public image_manipulator
    {
    public:
        line(coordinate_type x1, coordinate_type y1, coordinate_type x2, coordinate_type y2) : _x1{ x1 }, _y1{ y1 }, _x2{ x2 }, _y2{ y2 } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x1, _y1, _x2, _y2;
    };

    class hline : public image_manipulator
    {
    public:
        hline(coordinate_type x, coordinate_type y, coordinate_type length) : _x{ x }, _y{ y }, _length{ length } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x, _y, _length;
    };

    class vline : public image_manipulator
    {
    public:
        vline(coordinate_type x, coordinate_type y, coordinate_type length) : _x{ x }, _y{ y }, _length{ length } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x, _y, _length;
    };

    class rectangle : public image_manipulator
    {
    public:
        rectangle(coordinate_type x1, coordinate_type y1, coordinate_type x2, coordinate_type y2) : _x1{ x1 }, _y1{ y1 }, _x2{ x2 }, _y2{ y2 } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x1, _y1, _x2, _y2;
    };

    class circle : public image_manipulator
    {
    public:
        circle(coordinate_type x, coordinate_type y, coordinate_type radius) : _x{ x }, _y{ y }, _radius{ radius } {}

    protected:
        void manip(image & i) override;

    private:
        coordinate_type _x, _y, _radius;
    };



    //                                                                                                                                                                                   
    //                                                                                                                                                                                   
    //    _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____  
    //   |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| 
    //                                                                                                                                                                                   
    //                                                                                                                                                                                   

    class event
    {
    public:
        enum class key_modifier_t : uint32_t {
            none        = 0x0000,
            right_alt   = 0x0001,
            left_alt    = 0x0002,
            right_ctrl  = 0x0004,
            lect_ctrl   = 0x0008,
            shift       = 0x0010,
            num_lock    = 0x0020,
            scroll_lock = 0x0040,
            caps_lock   = 0x0080,
            any_alt     = right_alt | left_alt,
            any_ctrl    = right_ctrl | lect_ctrl,
            any         = any_alt | any_ctrl | shift | num_lock | scroll_lock | caps_lock,
        };
    };

    class key_event : public event
    {
    public:
        using ascii_char_t = char;
        using unicode_char_t = wchar_t;
        using virtual_char_t = uint16_t;

        enum class trigger_action_t : bool {
            key_down = true,
            key_up = false
        };

    private:
        ascii_char_t _ascii_value;
        unicode_char_t _unicode_value;
        virtual_char_t _virtual_value;
        size_t _occurrence;
        trigger_action_t _trigger_action;
        key_modifier_t _key_modifier;

        key_event(ascii_char_t ascii_value, unicode_char_t unicode_value, virtual_char_t virtual_value, size_t occurrence, trigger_action_t trigger_action, key_modifier_t key_modifier) :
            _ascii_value{ ascii_value }, _unicode_value{ unicode_value }, _virtual_value{ virtual_value }, _occurrence{ occurrence }, _trigger_action{ trigger_action }, _key_modifier{ key_modifier }
        {}

        friend class console_events;
        friend class csl_events;

    public:
        // Return input key translate to ascii counterpart.
        ascii_char_t ascii_value() const;
        // Return input key translate to unicode counterpart.
        unicode_char_t unicode_value() const;
        // Return input key translate to virtual-key-code counterpart (Windows encoding).
        virtual_char_t virtual_value() const;
        // Return the number of occurence (repeated key).
        size_t occurrence() const;

        // Return true if the action was a key down.
        bool key_down() const;
        // Return true if the action was a key up.
        bool key_up() const;
        // Return true if action was keyAction.
        bool trigger_action(trigger_action_t trigger) const;
        // Return true if keyModifier was activated.
        bool modifier_match(key_modifier_t mod) const;
        bool modifier_used(key_modifier_t mod) const;

        std::string to_string_info() const;
    };





    class mouse_event : public event
    {
    public:
        using coordinate_t = int16_t;

        enum class trigger_action_t : bool {
            button_pressed_released = 0x0000,
            moved = 0x0001,
            double_clicked = 0x0002,
            vertical_wheeled = 0x0004,
            horizontal_wheeled = 0x0008,
        };

        enum class state_button_t : uint8_t {
            none    = 0x0000,
            left    = 0x0001,
            right   = 0x0002,
            left_2  = 0x0004,
            left_3  = 0x0008,
            left_4  = 0x0010,
        };

    private:
        coordinate_t _x, _y;
        trigger_action_t _trigger_action;
        state_button_t _state_button;
        key_modifier_t _key_modifier;

        mouse_event(coordinate_t x, coordinate_t y, trigger_action_t trigger_action, state_button_t state_button, key_modifier_t key_modifier) :
            _x{ x }, _y{ y }, _trigger_action{ trigger_action }, _state_button{ state_button }, _key_modifier{ key_modifier }
        {}

        friend class console_events;
        friend class csl_events;

    public:
        coordinate_t x() const;
        coordinate_t y() const;

        trigger_action_t trigger_action() const;
        state_button_t state_button() const;
        key_modifier_t key_modifier() const;

        bool button_press(state_button_t state_button) const;
        bool button_release(state_button_t state_button) const;

        bool modifier_match(key_modifier_t mod) const;
        bool modifier_used(key_modifier_t mod) const;

        std::string to_string_info() const;
    };


    template <typename EventType>
    class events
    {
        static_assert(std::is_base_of_v<event, EventType> && !std::is_same_v<event, EventType>, "Invalid template parameter in events : EventType must inherit of event class (but not event).");
        using events_type = std::list<EventType>;

    public:
        using event_type = EventType;
        using size_type = typename events_type::size_type;
        using action_type = void(EventType const &);

        class filter 
        {
        public:
            operator filter&() { return *this; }
            virtual bool is_filtered(EventType const & e) const = 0;
        };

        size_type count() const { return _events.size(); }
        EventType next_event() const {
            if (_events.size() == 0) {
                throw std::logic_error("Logical error in events::next_key_event : no more event to extract.");
            }

            EventType e{ _events.front() };
            _events.pop_front();

            return e;
        }
        void for_each_event_do(std::function<action_type> f) {
            std::for_each(_events.begin(), _events.end(), f);
            _events.clear();
        }

        template <typename EventFilter> 
        static console& add_filter(console & c) {
            static_assert(std::is_base_of_v<filter, EventFilter>, "Invalid template parameter in events::add_filter : EventFilter must inherit from events::filter.");
            _filters.emplace_back(new EventFilter);
            return c;
        }
        static console& clear_filters(console & c) {
            _filters.clear();
            return c;
        }


    private:
        mutable events_type _events;
        static std::list<std::unique_ptr<filter>> _filters;
        friend class csl_events;

        static bool is_filtered(EventType const & e) {
            return std::any_of(begin(_filters), end(_filters), [&e](auto const & f)->bool { return f->is_filtered(e); });
        }

        friend class console_events;
    };

    template <typename EventType>
    std::list<std::unique_ptr<typename events<EventType>::filter>> events<EventType>::_filters;

    using key_events = events<key_event>;
    using mouse_events = events<mouse_event>;


    class key_filter_down : public key_events::filter
    {
    public:
        bool is_filtered(key_events::event_type const & e) const override { return e.key_down(); }
    };

    class key_filter_up : public key_events::filter
    {
    public:
        bool is_filtered(key_events::event_type const & e) const override { return e.key_up(); }
    };

    //class key_filter_modifiers : public key_events::filter
    //{
    //public:
    //    bool is_filtered(key_events::event_type const & e) const override { return e.modifier_used(event::key_modifier_t::any); }
    //};




    //class csl_events : public detail::base_console_manip<csl_events>
    //{
    //public:
    //    using size_type = size_t;

    //    explicit csl_events(key_events & k_event) : _key_events(k_event), _mouse_events() {}
    //    explicit csl_events(mouse_events & m_events) : _key_events(), _mouse_events(m_events) {}
    //    explicit csl_events(key_events & k_event, mouse_events & m_events) : _key_events(k_event), _mouse_events(m_events) {}

    //    static console & enable_mouse_tracking(console & c) {}
    //    static console & disable_mouse_tracking(console & c) {}

    //private:
    //    template <typename t> friend class detail::base_console_manip;
    //    //void insert();
    //    void extract();

    //    detail::omni<key_events> _key_events;
    //    detail::omni<mouse_events> _mouse_events;
    //};



    class console_events
    {
    public:
        using key_event_action_t = void(key_event const &);
        using mouse_event_action_t = void(mouse_event const &);

        using key_events_t = std::list<key_event>;
        using mouse_events_t = std::list<mouse_event>;

        console_events() = default;

        key_events_t::size_type key_events_count() const;
        key_event next_key_event() const;
        void for_each_key_event_do(std::function<key_event_action_t> f);

        mouse_events_t::size_type mouse_events_count() const;
        mouse_event next_mouse_event() const;
        void for_each_mouse_event_do(std::function<mouse_event_action_t> f);

        void read_events();

        static console & enable_mouse_tracking(console & c);
        static console & disable_mouse_tracking(console & c);

    private:
        mutable key_events_t _key_events;
        mutable mouse_events_t _mouse_events;
    };

}



//                                                                                                                                                                                   
//                                                                                                                                                                                   
//    _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____   _____  
//   |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____| 
//                                                                                                                                                                                   
//                                                                                                                                                                                   


template <typename t, typename = std::enable_if_t<std::is_base_of_v<windows_console::detail::base_console_manip<t>, t> && t::insertion_enabled(), int>>
inline windows_console::console& operator<<(windows_console::console & c, t & manip) { manip.do_insert(); return c; }
template <typename t, typename = std::enable_if_t<std::is_base_of_v<windows_console::detail::base_console_manip<t>, t> && t::insertion_enabled(), int>>
inline windows_console::console& operator<<(windows_console::console & c, t && manip) { manip.do_insert(); return c; }


template <typename t, typename = std::enable_if_t<std::is_base_of_v<windows_console::detail::base_console_manip<t>, t> && t::extraction_enabled(), int>>
inline windows_console::console& operator>>(windows_console::console & c, t & manip) { manip.do_extract(); return c; }
template <typename t, typename = std::enable_if_t<std::is_base_of_v<windows_console::detail::base_console_manip<t>, t> && t::extraction_enabled(), int>>
inline windows_console::console& operator>>(windows_console::console & c, t && manip) { manip.do_extract(); return c; }


inline windows_console::console& operator<<(windows_console::console & c, windows_console::console&(*f)(windows_console::console&)) { f(c); return c; }
inline windows_console::console& operator>>(windows_console::console & c, windows_console::console_events & e) { e.read_events(); return c; }


//template <typename t, typename = std::enable_if_t<std::is_base_of_v<win_console::image_manipulator, t>, int>>
//inline win_console::image& operator<<(win_console::image & i, t & m) { m.manip(i); return i; }
//template <typename t, typename = std::enable_if_t<std::is_base_of_v<win_console::image_manipulator, t>, int>>
//inline win_console::image& operator<<(win_console::image & i, t && m) { m.manip(i); return i; }

//template <typename t, typename = std::enable_if_t<std::is_base_of_v<win_console::image_manipulator, t>, int>>
inline windows_console::image& operator<<(windows_console::image & i, windows_console::image_manipulator & m) { m.manip(i); return i; }
//template <typename t, typename = std::enable_if_t<std::is_base_of_v<win_console::image_manipulator, t>, int>>
inline windows_console::image& operator<<(windows_console::image & i, windows_console::image_manipulator && m) { m.manip(i); return i; }

inline windows_console::image& operator<<(windows_console::image & i, windows_console::image&(*f)(windows_console::image&)) { f(i); return i; }



#pragma warning( default : 4624 ) // destructor was implicitly defined as deleted

#endif // _WINDOWS_CONSOLE_H_