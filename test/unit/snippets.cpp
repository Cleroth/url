    //
// Copyright (c) 2022 Alan Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#include "test_suite.hpp"

#include <boost/container/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/core/ignore_unused.hpp>

//[snippet_headers_1
#include <boost/url.hpp>
//]

#include <algorithm>
#include <iostream>
#include <cctype>

//[snippet_headers_3
#include <boost/url.hpp>
using namespace boost::urls;
//]

#include <iostream>

void
using_url_views()
{
    //[snippet_parsing_1
    string_view s = "https://user:pass@example.com:443/path/to/my%2dfile.txt?id=42&name=John%20Doe+Jingleheimer%2DSchmidt#page%20anchor";
    //]

    {
        //[snippet_parsing_2
        result<url_view> r = parse_uri( s );
        //]
    }

    {
        result<url_view> r = parse_uri( s );
        //[snippet_parsing_3
        url_view u = r.value();
        //]
    }

    {
        result<url_view> r = parse_uri( s );
        //[snippet_parsing_4
        url_view u = *r;
        //]
    }

    url_view u = parse_uri( s ).value();

    //[snippet_accessing_1
    std::cout <<
        "url       : " << u             << "\n"
        "scheme    : " << u.scheme()    << "\n"
        "authority : " << u.authority() << "\n"
        "userinfo  : " << u.userinfo()  << "\n"
        "user      : " << u.user()      << "\n"
        "password  : " << u.password()  << "\n"
        "host      : " << u.host()      << "\n"
        "port      : " << u.port()      << "\n"
        "path      : " << u.path()      << "\n"
        "query     : " << u.query()     << "\n"
        "fragment  : " << u.fragment()  << "\n";
    //]

    //[snippet_accessing_1b
    for (auto seg: u.segments())
        std::cout << seg << "\n";
    std::cout << "\n";
    for (auto param: u.params())
        std::cout << param.key << ": " << param.value << "\n";
    //]

    {
        //[snippet_accessing_2a
        url_view u1 = parse_uri( "http://www.example.com" ).value();
        std::cout << "fragment 1 : " << u1.fragment() << "\n\n";
        //]
    }

    {
        //[snippet_accessing_2b
        url_view u2 = parse_uri( "http://www.example.com/#" ).value();
        std::cout << "fragment 2 : " << u2.fragment() << "\n\n";
        //]
    }

    {
        //[snippet_accessing_3a
        url_view u1 = parse_uri( "http://www.example.com" ).value();
        std::cout << "has fragment 1 : " << u1.has_fragment() << "\n";
        std::cout << "fragment 1 : " << u1.fragment() << "\n\n";
        //]

        //[snippet_accessing_3b
        url_view u2 = parse_uri( "http://www.example.com/#" ).value();
        std::cout << "has fragment 2 : " << u2.has_fragment() << "\n";
        std::cout << "fragment 2 : " << u2.fragment() << "\n\n";
        //]
    }

    {
        //[snippet_accessing_4
        std::cout <<
            "url       : " << u                     << "\n"
            "scheme    : " << u.scheme()            << "\n"
            "authority : " << u.encoded_authority() << "\n"
            "userinfo  : " << u.encoded_userinfo()  << "\n"
            "user      : " << u.encoded_user()      << "\n"
            "password  : " << u.encoded_password()  << "\n"
            "host      : " << u.encoded_host()      << "\n"
            "port      : " << u.port()              << "\n"
            "path      : " << u.encoded_path()      << "\n"
            "query     : " << u.encoded_query()     << "\n"
            "fragment  : " << u.encoded_fragment()  << "\n";
        //]
    }

    {
        //[snippet_decoding_1
        std::string str;
        u.query().assign_to(str);
        str += "\n";
        u.fragment().append_to(str);
        std::cout << str << "\n";
        //]
    }
    {
        url u1 = u;
        url u2 = u;
        //[snippet_decoding_2
        u1.set_host(u2.host());
        //]
        std::cout << u1 << "\n";
    }
    {
        //[snippet_decoding_3
        boost::filesystem::path p;
        for (auto seg: u.segments())
            p /= seg;
        std::cout << "path: " << p << "\n";
        //]
    }
// transparent std::equal_to<> required
#if BOOST_CXX_VERSION >= 201402L && !defined(BOOST_CLANG)
    {
        auto handle_route = [](
            std::vector<std::string> const&,
            url_view)
        {};

        //[snippet_decoding_4a
        auto match = [](
            std::vector<std::string> const& route,
            url_view u)
        {
            auto segs = u.segments();
            if (route.size() != segs.size())
                return false;
            return std::equal(
                route.begin(),
                route.end(),
                segs.begin());
        };
        //]
        //[snippet_decoding_4b
        std::vector<std::string> route =
            {"community", "reviews.html"};
        if (match(route, u))
        {
            handle_route(route, u);
        }
        //]
    }
#endif
    {
        //[snippet_decoding_5a
        auto function = [](string_view str)
        {
            std::cout << str << "\n";
        };
        //]
        //[snippet_decoding_5b
        function(u.query().to_string());
        //]
    }

    {
        //[snippet_allocators_1
        // VFALCO - Fix me!
        //]
    }

    {
        //[snippet_compound_elements_1
        segments_view segs = u.segments();
        for( auto v : segs )
        {
            std::cout << v << "\n";
        }
        //]
    }

    {
        //[snippet_encoded_compound_elements_1
        segments_view segs = u.segments();

        for( auto v : segs )
        {
            std::cout << v << "\n";
        }
        //]
    }

    {
        //[snippet_encoded_compound_elements_2
        params_view params = u.params();

        for( auto v : params )
        {
            std::cout <<
                "key = " << v.key <<
                ", value = " << v.value << "\n";
        }
        //]
    }
}

void
using_urls()
{
    string_view s = "https://user:pass@www.example.com:443/path/to/my%2dfile.txt?id=42&name=John%20Doe#page%20anchor";

    //[snippet_quicklook_modifying_1
    url u = parse_uri( s ).value();
    //]

    //[snippet_quicklook_modifying_1b
    static_url<1024> su = parse_uri( s ).value();
    //]
    (void)su;

    //[snippet_quicklook_modifying_2
    u.set_scheme( "https" );
    //]

    //[snippet_quicklook_modifying_3
    u.set_scheme( scheme::https ); // equivalent to u.set_scheme( "https" );
    //]

    //[snippet_quicklook_modifying_4
    u.set_host( parse_ipv4_address( "192.168.0.1" ).value() )
        .set_port( 8080 )
        .remove_userinfo();
    std::cout << u << "\n";
    //]

    //[snippet_quicklook_modifying_5
    params p = u.params();
    p.emplace_at(p.find("name"), "name", "Vinnie Falco");
    std::cout << u << "\n";
    //]
}

void
parsing_urls()
{
    //[snippet_parsing_url_1
    result< url_view > r = parse_uri( "https://www.example.com/path/to/file.txt" );
    if( r.has_value() )                    // parsing was successful
    {
        url_view u = r.value();      // extract the url_view
        std::cout << u << "\n";            // format the URL to cout
    }
    else
    {
        std::cout << r.error().message();  // parsing failure; print error
    }
    //]

    //[snippet_parsing_url_2
    // This will hold our copy
    std::shared_ptr<url_view const> sp;
    {
        std::string s = "/path/to/file.txt";

        // result::value() will throw an exception if an error occurs
        url_view u = parse_relative_ref( s ).value();

        // create a copy with ownership and string lifetime extension
        sp = u.persist();

        // At this point the string goes out of scope
    }

    // but `*sp` remains valid since it has its own copy
    std::cout << *sp << "\n";
    //]

    {
        //[snippet_parsing_url_3
        // This will hold our mutable copy
        url v;
        {
            std::string s = "/path/to/file.txt";

            // result::value() will throw an exception if an error occurs
            v = parse_relative_ref(s).value();

            // At this point the string goes out of scope
        }

        // but `v` remains valid since it has its own copy
        std::cout << v << "\n";

        // and it's mutable
        v.set_encoded_fragment("anchor");

        std::cout << v << "\n";
        //]
    }
}

void
parsing_scheme()
{
    {
        //[snippet_parsing_scheme_1
        string_view s = "mailto:name@email.com";
        url_view u = parse_uri( s ).value();
        std::cout << u.scheme() << "\n";
        //]
    }
    {
        string_view s = "mailto:name@email.com";
        //[snippet_parsing_scheme_2
        url_view u = parse_uri( s ).value();
        if (u.has_scheme())
        {
            std::cout << u.scheme() << "\n";
        }
        //]
    }
    {
        //[snippet_parsing_scheme_3
        string_view s = "file://host/path/to/file";
        url_view u = parse_uri( s ).value();
        if (u.scheme_id() == scheme::file)
        {
            // handle file
        }
        //]
    }
}

void
parsing_authority()
{
    {
        //[snippet_parsing_authority_1
        string_view s = "https:///path/to_resource";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n"
            "scheme:        " << u.scheme()        << "\n"
            "has authority: " << u.has_authority() << "\n"
            "authority:     " << u.authority()     << "\n"
            "path:          " << u.encoded_path()  << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_2
        string_view s = "https://www.boost.org";
        url_view u = parse_uri( s ).value();
        std::cout << "scheme:        " << u.scheme()            << "\n"
                     "has authority: " << u.has_authority()     << "\n"
                     "authority:     " << u.authority()         << "\n"
                     "path:          " << u.path()              << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_3
        string_view s = "https://www.boost.org/users/download/";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n"
            "scheme:        " << u.scheme()        << "\n"
            "has authority: " << u.has_authority() << "\n"
            "authority:     " << u.authority()     << "\n"
            "path:          " << u.path()          << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_4
        string_view s = "https://www.boost.org/";
        url_view u = parse_uri( s ).value();
        std::cout << "scheme:        " << u.scheme()            << "\n"
                     "has authority: " << u.has_authority()     << "\n"
                     "authority:     " << u.authority()         << "\n"
                     "path:          " << u.path()              << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_5
        string_view s = "mailto:John.Doe@example.com";
        url_view u = parse_uri( s ).value();
        std::cout << "scheme:        " << u.scheme()            << "\n"
                     "has authority: " << u.has_authority()     << "\n"
                     "authority:     " << u.authority()         << "\n"
                     "path:          " << u.path()              << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_6
        string_view s = "mailto://John.Doe@example.com";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n"
            "scheme:        " << u.scheme()   << "\n"
            "has authority: " << u.has_authority()     << "\n"
            "authority:     " << u.authority()         << "\n"
            "path:          " << u.path()              << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_7
        string_view s = "https://john.doe@www.example.com:123/forum/questions/";
        url_view u = parse_uri( s ).value();
        std::cout << "scheme:        " << u.scheme()   << "\n"
            "has authority: " << u.has_authority()     << "\n"
            "authority:     " << u.authority()         << "\n"
            "host:          " << u.host()              << "\n"
            "userinfo:      " << u.userinfo()          << "\n"
            "port:          " << u.port()              << "\n"
            "path:          " << u.path()              << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_8
        string_view s = "https://john.doe@www.example.com:123/forum/questions/";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n"
            "host:          " << u.host()                  << "\n"
            "host and port: " << u.encoded_host_and_port() << "\n"
            "port:          " << u.port()                  << "\n"
            "port number:   " << u.port_number()           << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_9
        string_view s = "https://john.doe@192.168.2.1:123/forum/questions/";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n"
            "host:          " << u.host()                  << "\n"
            "host and port: " << u.encoded_host_and_port() << "\n"
            "port:          " << u.port()                  << "\n"
            "port number:   " << u.port_number()           << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_10
        string_view s = "https://www.boost.org/users/download/";
        url_view u = parse_uri( s ).value();
        switch (u.host_type())
        {
        case host_type::name:
            // resolve name
        case host_type::ipv4:
        case host_type::ipv6:
        case host_type::ipvfuture:
            // connect to ip
            break;
        case host_type::none:
            // handle empty host URL
            break;
        }
        //]
    }
    {
        //[snippet_parsing_authority_11
        string_view s = "https://john.doe:123456@www.somehost.com/forum/questions/";
        url_view u = parse_uri( s ).value();
        std::cout << u << "\n\n"
            "has_userinfo:     " << u.has_userinfo()     << "\n"
            "userinfo:         " << u.userinfo()         << "\n"
            "user:             " << u.user()             << "\n\n"
            "has_password:     " << u.has_password()     << "\n"
            "password:         " << u.password()         << "\n";
        //]
    }
    {
        std::cout << "snippet_parsing_authority_12\n";
        //[snippet_parsing_authority_12
        string_view s = "www.example.com:80";
        authority_view a = parse_authority( s ).value();
        std::cout << a << "\n\n"
            // host and port
            "host_and_port:         " << a.encoded_host_and_port() << "\n"
            "host:                  " << a.host()         << "\n"
            "port:                  " << a.port()         << "\n"
            "port number:           " << a.port_number()  << "\n\n"
            // userinfo
            "has_userinfo:          " << a.has_userinfo() << "\n"
            "userinfo:              " << a.userinfo()     << "\n"
            // user
            "user:                  " << a.user()         << "\n\n"
            // password
            "has_password:          " << a.has_password() << "\n"
            "password:              " << a.password()     << "\n";
        //]
    }
    {
        //[snippet_parsing_authority_13
        string_view s = "user:pass@www.example.com:443";
        authority_view a = parse_authority( s ).value();
        std::cout << a << "\n\n"
            // host and port
            "host_and_port:         " << a.encoded_host_and_port() << "\n"
            "host:                  " << a.host()         << "\n"
            "port:                  " << a.port()         << "\n"
            "port number:           " << a.port_number()  << "\n\n"
            // userinfo
            "has_userinfo:          " << a.has_userinfo()     << "\n"
            "userinfo:              " << a.userinfo()         << "\n\n"
            // user
            "user:                  " << a.user()             << "\n\n"
            // password
            "has_password:          " << a.has_password()     << "\n"
            "password:              " << a.password()         << "\n";
        //]
    }
}

void
parsing_path()
{
    {
        //[snippet_parsing_path_1
        string_view s = "https://www.boost.org/doc/libs/";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
            << "path:             " << u.path()             << "\n"
            << "path:             " << u.encoded_path()     << "\n"
            << "segments:         " << u.segments()         << "\n"
            << "encoded_segments: " << u.encoded_segments() << "\n";
        //]

        //[snippet_parsing_path_1_b
        std::cout << u.encoded_segments().size() << " segments\n";
        for (auto seg: u.encoded_segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        //[snippet_parsing_path_2
        string_view s = "https://www.boost.org/doc/libs";
        url_view u = parse_uri(s).value();
        std::cout << u.segments().size() << " segments\n";
        for (auto seg: u.segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        //[snippet_parsing_path_3
        string_view s = "https://www.boost.org";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
            << "path:             " << u.encoded_path()     << "\n";
        //]
    }

    {
        //[snippet_parsing_path_4
        string_view s = "https://www.boost.org//doc///libs";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
                  "path:             " << u.encoded_path()     << "\n"
                  "encoded segments: " << u.encoded_segments() << "\n"
                  "segments:         " << u.segments()         << "\n";
        std::cout << u.encoded_segments().size() << " segments\n";
        for (auto seg: u.encoded_segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        {
            //[snippet_parsing_path_5_a
            string_view s = "https://www.boost.org";
            url_view    u = parse_uri(s).value();
            std::cout << u << "\n"
                      << "path:     " << u.encoded_host()            << "\n"
                      << "path:     " << u.encoded_path()            << "\n"
                      << "segments: " << u.encoded_segments().size() << "\n";
            //]
        }
        {
            //[snippet_parsing_path_5_b
            string_view s = "https://www.boost.org/";
            url_view    u = parse_uri(s).value();
            std::cout << u << "\n"
                      << "host:     " << u.encoded_host()            << "\n"
                      << "path:     " << u.encoded_path()            << "\n"
                      << "segments: " << u.encoded_segments().size() << "\n";
            //]
        }
        {
            //[snippet_parsing_path_5_c
            string_view s = "https://www.boost.org//";
            url_view    u = parse_uri(s).value();
            std::cout << u << "\n"
                      << "host:     " << u.encoded_host()            << "\n"
                      << "path:     " << u.encoded_path()            << "\n"
                      << "segments: " << u.encoded_segments().size() << "\n";
            //]
        }
    }

    {
        //[snippet_parsing_path_6
        string_view s = "https://www.boost.org//doc/libs/";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
                  "authority: " << u.encoded_authority() << "\n"
                  "path:      " << u.encoded_path()      << "\n";
        std::cout << u.encoded_segments().size() << " segments\n";
        for (auto seg: u.encoded_segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        //[snippet_parsing_path_7
        string_view s = "https://doc/libs/";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
                  "authority: " << u.encoded_authority() << "\n"
                  "path:      " << u.encoded_path()      << "\n";
        std::cout << u.encoded_segments().size() << " segments\n";
        for (auto seg: u.encoded_segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        //[snippet_parsing_path_8
        string_view s = "https://www.boost.org/doc@folder/libs:boost";
        url_view    u = parse_uri(s).value();
        std::cout << u << "\n"
                  "authority: " << u.encoded_authority() << "\n"
                  "path:      " << u.encoded_path()      << "\n";
        std::cout << u.encoded_segments().size() << " segments\n";
        for (auto seg: u.encoded_segments())
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }

    {
        //[snippet_parsing_path_9
        string_view s = "/doc/libs";
        segments_view p = parse_path(s).value();
        std::cout << "path: " << p << "\n";
        std::cout << p.size() << " segments\n";
        for (auto seg: p)
        {
            std::cout << "segment: " << seg << "\n";
        }
        //]
    }
}

void
parsing_query()
{
    {
        //[snippet_parsing_query_1
        string_view s = "https://www.example.com/get-customer.php?id=409&name=Joe&individual";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query:     " << u.has_query()     << "\n"
                  "query:         " << u.query()         << "\n";
        std::cout << u.params().size() << " parameters\n";

        for (auto p: u.params())
        {
            if (p.has_value)
            {
                std::cout <<
                    "parameter: <" << p.key <<
                    ", " << p.value << ">\n";
            } else {
                std::cout << "parameter: " << p.key << "\n";
            }
        }
        //]
    }
    {
        //[snippet_parsing_query_2
        string_view s = "https://www.example.com/get-customer.php?key-1=value-1&key-2=&key-3&&=value-2";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query:     " << u.has_query()     << "\n"
                  "encoded query: " << u.encoded_query() << "\n"
                  "query:         " << u.query()         << "\n";
        std::cout << u.encoded_params().size() << " parameters\n";
        for (auto p: u.encoded_params())
        {
            if (p.has_value)
            {
                std::cout <<
                    "parameter: <" << p.key <<
                    ", " << p.value << ">\n";
            } else {
                std::cout << "parameter: " << p.key << "\n";
            }
        }
        //]
    }
    {
        //[snippet_parsing_query_3
        string_view s = "https://www.example.com/get-customer.php?email=joe@email.com&code=a:2@/!";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query:     " << u.has_query()     << "\n"
                  "encoded query: " << u.encoded_query() << "\n"
                  "query:         " << u.query()         << "\n";
        std::cout << u.encoded_params().size() << " parameters\n";
        for (auto p: u.encoded_params())
        {
            if (p.has_value)
            {
                std::cout <<
                    "parameter: <" << p.key <<
                    ", " << p.value << ">\n";
            } else {
                std::cout << "parameter: " << p.key << "\n";
            }
        }
        //]
    }
    {
        //[snippet_parsing_query_4
        string_view s = "https://www.example.com/get-customer.php?name=joe";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "query: " << u.query() << "\n";
        //]
    }
    {
        //[snippet_parsing_query_5
        string_view s = "https://www.example.com/get-customer.php";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query: " << u.has_query() << "\n"
                  "query:     " << u.query()     << "\n";
        //]
    }
    {
        //[snippet_parsing_query_6
        string_view s = "https://www.example.com/get-customer.php?name=John%20Doe";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query:     " << u.has_query()     << "\n"
                  "encoded query: " << u.encoded_query() << "\n"
                  "query:         " << u.query()         << "\n";
        //]
    }
    {
        //[snippet_parsing_query_7
        string_view s = "https://www.example.com/get-customer.php?name=John%26Doe";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has query:     " << u.has_query()     << "\n"
                  "encoded query: " << u.encoded_query() << "\n"
                  "query:         " << u.query()         << "\n";
        //]
    }
}

void
parsing_fragment()
{
    {
        //[snippet_parsing_fragment_1
        string_view s = "https://www.example.com/index.html#section%202";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has fragment:     " << u.has_fragment()     << "\n"
                  "fragment:         " << u.fragment()         << "\n"
                  "encoded fragment: " << u.encoded_fragment() << "\n";
        //]
    }
    {
        //[snippet_parsing_fragment_2_a
        string_view s = "https://www.example.com/index.html#";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has fragment:     " << u.has_fragment()     << "\n"
                  "fragment:         " << u.fragment()         << "\n";
        //]
    }
    {
        //[snippet_parsing_fragment_2_b
        string_view s = "https://www.example.com/index.html";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has fragment:     " << u.has_fragment()     << "\n"
                  "fragment:         " << u.fragment()         << "\n";
        //]
    }
    {
        //[snippet_parsing_fragment_3
        string_view s = "https://www.example.com/index.html#code%20:a@b?c/d";
        url_view u = parse_uri(s).value();
        std::cout << u << "\n"
                  "has fragment:     " << u.has_fragment()     << "\n"
                  "fragment:         " << u.fragment()         << "\n";
        //]
    }
}

void
using_modifying()
{
    {
        //[snippet_modifying_1
        string_view s = "https://www.example.com";
        url_view u = parse_uri(s).value();
        url v(u);
        //]

        //[snippet_modifying_2
        std::cout << v << "\n"
            "scheme:        " << v.scheme()            << "\n"
            "has authority: " << v.has_authority()     << "\n"
            "authority:     " << v.encoded_authority() << "\n"
            "path:          " << v.encoded_path()      << "\n";
        //]

        //[snippet_modifying_3
        v.set_host("my website.com");
        v.set_path("my file.txt");
        v.set_query("id=42&name=John Doe");
        std::cout << v << "\n";
        //]

        //[snippet_modifying_4
        v.set_scheme("http");
        std::cout << v << "\n";
        //]

        //[snippet_modifying_5
        v.set_host("www.my example.com");
        std::cout << v << "\n";
        //]


    }
}

void
grammar_parse()
{
    {
        //[snippet_parse_1
        // VFALCO we should not show this example
        /*
        string_view s = "http:after_scheme";
        const char* it = s.begin();
        auto rv = grammar::parse(it, s.end(), scheme_rule() );
        if( ! rv )
        {
            std::cout << "scheme: " << rv->scheme << '\n';
            std::cout << "suffix: " << it << '\n';
        }
        */
        //]
    }

    {
        //[snippet_parse_2
        // VFALCO This needs refactoring
        /*
        string_view s = "?key=value#anchor";
        const char* it = s.begin();
        error_code ec;
        if (grammar::parse(it, s.end(), ec, r1))
        {
            auto r2 = grammar::parse( it, s.end(), fragment_part_rule );
            if( r2 )
            {
                std::cout << "query: " << r1.query_part << '\n';
                std::cout << "fragment: " << std::get<1>(*r2.value()).encoded() << '\n';
            }
        }
        */
        //]
    }

    {
        //[snippet_parse_3
        // VFALCO This needs refactoring
        /*
        string_view s = "?key=value#anchor";
        query_part_rule r1;
        const char* it = s.begin();
        error_code ec;
        auto r2 = grammar::parse( it, s.end(), ec, fragment_part_rule );
        if( ! ec.failed() )
        {
            std::cout << "query: " << r1.query_part << '\n';
            std::cout << "fragment: " << r2.fragment.encoded() << '\n';
        }
        */
        //]
    }

    {
        //[snippet_parse_4
        /* VFALCO This will be removed
        string_view s = "http://www.boost.org";
        uri_rule r;
        error_code ec;
        if (grammar::parse_string(s, ec, r))
        {
            std::cout << "scheme: " << r.scheme_part.scheme << '\n';
            std::cout << "host: " << r.hier_part.authority.host.host_part << '\n';
        }
        */
        //]
    }
}

//[snippet_customization_1
/* VFALCO This needs rewriting
struct lowercase_rule
{
    string_view str;

    friend
    void
    tag_invoke(
        grammar::parse_tag const&,
        char const*& it,
        char const* const end,
        error_code& ec,
        lowercase_rule& t) noexcept
    {
        ec = {};
        char const* begin = it;
        while (it != end && std::islower(*it))
        {
            ++it;
        }
        t.str = string_view(begin, it);
    }
};
*/
//]

void
grammar_customization()
{
    {
        //[snippet_customization_2
        // VFALCO THIS NEEDS TO BE PORTED
        /*
        string_view s = "http:somelowercase";
        scheme_rule r1;
        lowercase_rule r2;
        error_code ec;
        if (grammar::parse_string(s, ec, r1, ':', r2))
        {
            std::cout << "scheme: " << r1.scheme << '\n';
            std::cout << "lower:  " << r2.str << '\n';
        }
        */
        //]
    }
}

//[code_charset_1
struct CharSet
{
    bool operator()( char c ) const noexcept;

    // These are both optional. If either or both are left
    // unspecified, a default implementation will be used.
    //
    char const* find_if( char const* first, char const* last ) const noexcept;
    char const* find_if_not( char const* first, char const* last ) const noexcept;
};
//]

//[snippet_mutable_string_exemplar
struct MutableString
{
    template< class InputIt >
    void assign( InputIt first, InputIt last );

    template< class InputIt >
    void append( InputIt first, InputIt last );
};
//]

void
modifying_path()
{
    {
        //[snippet_modifying_path_1
        url_view u = parse_uri("https://www.boost.org").value();
        //]
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 0u);
    }

    {
        //[snippet_modifying_path_2
        url_view u = parse_uri("https://www.boost.org/").value();
        //]
        BOOST_TEST(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 0u);
    }

    {
        //[snippet_modifying_path_3
        url u = parse_uri("https://www.boost.org/./a/../b").value();
        u.normalize();
        //]
        BOOST_TEST(u.is_path_absolute());
        BOOST_TEST_EQ(u.string(), "https://www.boost.org/b");
        BOOST_TEST_EQ(u.encoded_segments().size(), 1u);
    }

    {
        //[snippet_modifying_path_4
        // scheme and a relative path
        url_view u = parse_uri("https:path/to/file.txt").value();
        //]
        BOOST_TEST_EQ(u.scheme(), "https");
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 3u);
    }

    {
        //[snippet_modifying_path_5
        // scheme and an absolute path
        url_view u = parse_uri("https:/path/to/file.txt").value();
        //]
        BOOST_TEST_EQ(u.scheme(), "https");
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 3u);
    }

    {
        //[snippet_modifying_path_6
        // "//path" will be considered the authority component
        url_view u = parse_uri("https://path/to/file.txt").value();
        //]
        BOOST_TEST_EQ(u.scheme(), "https");
        BOOST_TEST(u.has_authority());
        BOOST_TEST(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 2u);
    }

    {
        //[snippet_modifying_path_7
        // only a relative path
        url_view u = parse_uri_reference("path-to/file.txt").value();
        //]
        BOOST_TEST_NOT(u.has_scheme());
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 2u);
    }

    {
        //[snippet_modifying_path_8
        // "path:" will be considered the scheme component
        // instead of a substring of the first segment
        url_view u = parse_uri_reference("path:to/file.txt").value();
        //]
        BOOST_TEST(u.has_scheme());
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 2u);
    }

    {
        //[snippet_modifying_path_9
        // "path" should not become the authority component
        url u = parse_uri("https:path/to/file.txt").value();
        u.set_encoded_path("//path/to/file.txt");
        //]
        BOOST_TEST_EQ(u.scheme(), "https");
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 4u);
    }

    {
        //[snippet_modifying_path_10
        // "path:to" should not make the scheme become "path:"
        url u = parse_uri_reference("path-to/file.txt").value();
        u.set_encoded_path("path:to/file.txt");
        //]
        BOOST_TEST_NOT(u.has_scheme());
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 2u);
    }

    {
        //[snippet_modifying_path_11
        // should not insert as "pathto/file.txt"
        url u = parse_uri_reference("to/file.txt").value();
        segments segs = u.segments();
        segs.insert(segs.begin(), "path");
        //]
        BOOST_TEST_NOT(u.has_scheme());
        BOOST_TEST_NOT(u.has_authority());
        BOOST_TEST_NOT(u.is_path_absolute());
        BOOST_TEST_EQ(u.encoded_segments().size(), 3u);
    }
}

//[snippet_using_static_pool_1
// VFALCO NOPE
//]

namespace boost {
namespace urls {

class snippets_test
{
public:
    void
    run()
    {
        ignore_unused(&using_url_views);
        ignore_unused(&using_urls);
        ignore_unused(&parsing_urls);
        ignore_unused(&parsing_scheme);
        ignore_unused(&parsing_authority);
        ignore_unused(&parsing_path);
        ignore_unused(&parsing_query);
        ignore_unused(&parsing_fragment);
        ignore_unused(&using_modifying);
        ignore_unused(&grammar_parse);
        ignore_unused(&grammar_customization);
        ignore_unused(&modifying_path);

        BOOST_TEST_PASS();
    }
};

TEST_SUITE(snippets_test, "boost.url.snippets");

} // urls
} // boost
