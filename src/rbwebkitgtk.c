/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */

/************************************************

  rbwebkitgtk.c -

    Ruby-GNOME2 Gtk::Webkit - Ruby bindings for WebKitGtk

    Copyright (C) 2008 Daniel Lucraft, All rights reserved.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

************************************************/

#include "ruby.h"

#include "rbgtk.h"

#include "webkit/webkit.h"

#include "rbwebkitgtkversion.h"

#define _WEBVIEW_SELF(s) (WEBKIT_WEB_VIEW(RVAL2GOBJ(s)))
#define _HISTITEM_SELF(s) (WEBKIT_WEB_HISTORY_ITEM(RVAL2GOBJ(s)))

/*
 * Class: Gtk::WebKit::WebView
 *
 * This class wraps the WebView widget in a Ruby class.  The
 * WebView is an HTML rendering widget based on Mozilla Gecko
 * provided by either Mozilla or Firefox.  You need to have
 * libwebkit.so in your library path to use and
 * and webkit.h in order to compile.
 *
 *  Gtk::WebKit::WebView.new
 *  ...
 *
 * Please see the sample application ruby-webkit for more info and
 * examples.
 *
 */


/* 
 * Class method: new
 *
 * Constructor for the Gtk::WebKit::WebView object.
 *
 * Returns: a newly created Gtk::WebKit::WebView widget.
 *
 */
static VALUE
wk_webview_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, WEBKIT_WEB_VIEW (webkit_web_view_new ()));
    return Qnil;
}

/*
 * Method: open(url)
 *
 * url: the url to load (String).
 *
 * This method starts loading the given url, and returns
 * immediately. The url should be in the form "http://www.gnome.org".
 *
 * Returns: self.
 *
 */

static VALUE
wk_webview_open(self, rb_url)
    VALUE self, rb_url;
{
    webkit_web_view_open (_WEBVIEW_SELF(self), RVAL2CSTR(rb_url));
    return self;
}

/*
 * Method: stop_loading
 *
 * Stops loading the current page.
 *
 * Returns: self.
 *
 */
static VALUE
wk_webview_stop_loading(self)
    VALUE self;
{
    webkit_web_view_stop_loading(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: can_go_back?
 *
 * This method reflects the status of the browsing history.
 *
 * Returns: True if the browser can go back one page.
 *
 */
static VALUE
wk_webview_can_go_back(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_can_go_back(_WEBVIEW_SELF(self)));
}

/*
 * Method: can_go_forward?
 *
 * This method reflects the status of the browsing history.
 *
 * Returns: True if the browser can go forward one page.
 *
 */
static VALUE
wk_webview_can_go_forward(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_can_go_forward(_WEBVIEW_SELF(self)));
}

/*
 * Method: go_back
 *
 * Tells the browser to go back one page in the history.
 *
 * Returns: the object itself.
 *
 */
static VALUE
wk_webview_go_back(self)
    VALUE self;
{
    webkit_web_view_go_back(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: go_forward
 *
 * Tells the browser to go one page forward in the history.
 *
 * Returns: the object itself.
 *
 */
static VALUE
wk_webview_go_forward(self)
    VALUE self;
{
    webkit_web_view_go_forward(_WEBVIEW_SELF(self));
    return self;
}


/*
 * Method: reload
 *
 * Reloads the current page.
 *
 * Returns: self.
 *
 */
static VALUE
wk_webview_reload(self)
    VALUE self;
{
    webkit_web_view_reload(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: load_html_string
 *
 * Displays the contents of an HTML string.
 *
 * Returns: self.
 *
 */

static VALUE
wk_webview_load_html_string(self, rb_content, rb_uri)
    VALUE self, rb_content, rb_uri;
{
    gchar* base_uri = NULL;
    if (rb_uri != Qnil)
        base_uri = RVAL2CSTR(rb_uri);
    webkit_web_view_load_html_string(_WEBVIEW_SELF(self), 
                                     RVAL2CSTR(rb_content),
                                     base_uri);
    return self;
}

/*
 * Method: execute_script
 *
 * Executes a string of JavaScript.
 *
 * Returns: self.
 *
 */

static VALUE
wk_webview_execute_script(self, rb_script)
    VALUE self, rb_script;
{
    webkit_web_view_execute_script(_WEBVIEW_SELF(self), 
                                   RVAL2CSTR(rb_script));
    return self;
}


/*
 * Class: Gtk::WebKit::WebHistoryItem
 *
 * This class wraps the WebKit WebHistoryItem object in a Ruby 
 * class.  The
 * Please see the sample application ruby-webkit for more info and
 * examples.
 *
 */


/* 
 * Class method: new
 *
 * Creates a new Gtk::WebKit::WebHistoryItem object with uri and 
 * title.
 *
 * Returns: a newly created Gtk::WebKit::WebHistoryItem object.
 *
 */
static VALUE
wk_histitem_initialize(self, rb_uri, rb_title)
    VALUE self, rb_uri, rb_title;
{
    G_INITIALIZE(self, WEBKIT_WEB_HISTORY_ITEM (
                     webkit_web_history_item_new_with_data (
                         RVAL2CSTR(rb_uri), 
                         RVAL2CSTR(rb_title)
                         )));
    return Qnil;
}

/*
 * Method: get_title
 *
 * Returns: the page title of the WebHistoryItem.
 *
 */
static VALUE
wk_histitem_get_title(self)
    VALUE self;
{
    gchar* title;
    title = (gchar *) webkit_web_history_item_get_title(_HISTITEM_SELF(self));
    return CSTR2RVAL(title);
}

/*
 * Method: get_uri
 *
 * Returns: the page uri of the WebHistoryItem.
 *
 */
static VALUE
wk_histitem_get_uri(self)
    VALUE self;
{
    gchar* title;
    title = (gchar *) webkit_web_history_item_get_uri(_HISTITEM_SELF(self));
    return CSTR2RVAL(title);
}


/*                                                           */
/*************************************************************/

/** INIT **/

void 
Init_rbwebkitgtk()
{
    VALUE rb_mWebKit = rb_eval_string("Gtk::WebKit");
    VALUE rb_cWebView = G_DEF_CLASS(WEBKIT_TYPE_WEB_VIEW, "WebView", rb_mWebKit);

    rb_define_method(rb_cWebView, "initialize", wk_webview_initialize, 0);
    rb_define_method(rb_cWebView, "open", wk_webview_open, 1);
    rb_define_method(rb_cWebView, "stop_loading", wk_webview_stop_loading, 0);
    rb_define_method(rb_cWebView, "can_go_back?", wk_webview_can_go_back, 0);
    rb_define_method(rb_cWebView, "can_go_forward?", wk_webview_can_go_forward, 0);
    rb_define_method(rb_cWebView, "go_back", wk_webview_go_back, 0);
    rb_define_method(rb_cWebView, "go_forward", wk_webview_go_forward, 0);
    rb_define_method(rb_cWebView, "reload", wk_webview_reload, 0);
    rb_define_method(rb_cWebView, "load_html_string", wk_webview_load_html_string, 2);
    rb_define_method(rb_cWebView, "execute_script", wk_webview_execute_script, 1);

    G_DEF_SETTERS(rb_cWebView);

    VALUE rb_cWebHistoryItem = G_DEF_CLASS(WEBKIT_TYPE_WEB_HISTORY_ITEM, "WebHistoryItem", rb_mWebKit);
    rb_define_method(rb_cWebHistoryItem, "initialize", wk_histitem_initialize, 2);
    rb_define_method(rb_cWebHistoryItem, "get_title", wk_histitem_get_title, 0);
    rb_define_method(rb_cWebHistoryItem, "get_uri", wk_histitem_get_title, 0);

//    G_DEF_SETTERS(rb_cWebHistoryItem);

}
