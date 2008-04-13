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
#define _BFLIST_SELF(s) (WEBKIT_WEB_BACK_FORWARD_LIST(RVAL2GOBJ(s)))

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
 * class. 
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
 * Method: get_alternate_title
 *
 * Returns: the alternate title of the WebHistoryItem.
 *
 */
static VALUE
wk_histitem_get_alternate_title(self)
    VALUE self;
{
    gchar* title;
    title = (gchar *) webkit_web_history_item_get_alternate_title(_HISTITEM_SELF(self));
    return CSTR2RVAL(title);
}

/*
 * Method: set_alternate_title
 *
 * Sets an alternate title for the WebHistoryItem.
 *
 * Returns: self.
 *
 */
static VALUE
wk_histitem_set_alternate_title(self, rb_title)
    VALUE self, rb_title;
{
    webkit_web_history_item_set_alternate_title(
        _HISTITEM_SELF(self),
        RVAL2CSTR(rb_title)
        );
    return self;
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
    gchar* uri;
    uri = (gchar *) webkit_web_history_item_get_uri(_HISTITEM_SELF(self));
    return CSTR2RVAL(uri);
}

/*
 * Method: get_original_uri
 *
 * Returns: the original uri of the WebHistoryItem.
 *
 */
static VALUE
wk_histitem_get_original_uri(self)
    VALUE self;
{
    gchar* uri;
    uri = (gchar *) webkit_web_history_item_get_uri(_HISTITEM_SELF(self));
    return CSTR2RVAL(uri);
}

/*
 * Method: get_last_visited_time_in_seconds
 *
 * Returns: a time in seconds that the WebHistoryItem was last visited,
 *          or nil if this WebHistoryItem has never been visited.
 *
 */
static VALUE
wk_histitem_get_last_visited_time_in_seconds(self)
    VALUE self;
{
    gdouble time;
    time = webkit_web_history_item_get_last_visited_time(_HISTITEM_SELF(self));
    if (time == 0)
        return Qnil;
    return LONG2NUM(time);
}


/*
 * Class: Gtk::WebKit::WebBackForwardList
 *
 * This class wraps the WebKitGtk WebBackForwardList GObject in a Ruby 
 * class. 
 * Please see the sample application ruby-webkit for more info and
 * examples.
 *
 */


/* 
 * Class method: new
 *
 * Creates a new Gtk::WebKit::WebBackForwardList object with an
 * associated WebView.
 *
 * Returns: a newly created Gtk::WebKit::WebBackForwardList object.
 *
 */
static VALUE
wk_bflist_initialize(self, rb_webview)
    VALUE self, rb_webview;
{
    G_INITIALIZE(self, WEBKIT_WEB_BACK_FORWARD_LIST (
                     webkit_web_back_forward_list_new_with_web_view (
                         _WEBVIEW_SELF(rb_webview)
                         )));
    return Qnil;
}

/*
 * Method: go_forward
 *
 * FIXME
 *
 * Returns: self.
 *
 */
static VALUE
wk_bflist_go_forward(self)
    VALUE self;
{
    webkit_web_back_forward_list_go_forward(_BFLIST_SELF(self));
    return self;
}


/*
 * Method: go_back
 *
 * FIXME
 *
 * Returns: self.
 *
 */
static VALUE
wk_bflist_go_back(self)
    VALUE self;
{
    webkit_web_back_forward_list_go_back(_BFLIST_SELF(self));
    return self;
}

/*
 * Method: contains_item?
 *
 * Whether the WebBackForwardList contains the WebHistoryItem.
 *
 * Returns: true or false.
 *
 */
static VALUE
wk_bflist_contains_item(self, rb_item)
    VALUE self, rb_item;
{
    gboolean has;
    has = webkit_web_back_forward_list_contains_item(
        _BFLIST_SELF(self),
        _HISTITEM_SELF(rb_item)
        );
    return CBOOL2RVAL(has);
}

/*
 * Method: go_to_item
 *
 * FIXME
 *
 * Returns: self.
 *
 */
static VALUE
wk_bflist_go_to_item(self, rb_item)
    VALUE self, rb_item;
{
    webkit_web_back_forward_list_go_to_item(
        _BFLIST_SELF(self),
        _HISTITEM_SELF(rb_item)
        );
    return self;
}

/*
 * Method: get_forward_list_with_limit
 *
 * Returns: an array of WebHistoryItems.
 *
 */
static VALUE
wk_bflist_get_forward_list_with_limit(self, rb_limit)
    VALUE self, rb_limit;
{
    GList* list;
    list = webkit_web_back_forward_list_get_forward_list_with_limit(
        _BFLIST_SELF(self),
        NUM2INT(rb_limit)
        );
    return GLIST2ARY(list);
}

/*
 * Method: get_back_list_with_limit
 *
 * Returns: an array of WebHistoryItems.
 *
 */

static VALUE
wk_bflist_get_back_list_with_limit(self, rb_limit)
    VALUE self, rb_limit;
{
    GList* list;
    list = webkit_web_back_forward_list_get_back_list_with_limit(
        _BFLIST_SELF(self),
        NUM2INT(rb_limit)
        );
    return GLIST2ARY(list);
}


/*
 * Method: get_back_item
 *
 * Returns: the WebHistoryItem that precedes the current item.
 *
 */
static VALUE
wk_bflist_get_back_item(self)
    VALUE self;
{
    WebKitWebHistoryItem* item;
    item = webkit_web_back_forward_list_get_back_item(_BFLIST_SELF(self));
    return GOBJ2RVAL(item); // FIXME: is this correct?
}

/*
 * Method: get_current_item
 *
 * Returns: the currrent WebHistoryItem in the WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_current_item(self)
    VALUE self;
{
    WebKitWebHistoryItem* item;
    item = webkit_web_back_forward_list_get_current_item(_BFLIST_SELF(self));
    return GOBJ2RVAL(item); // FIXME: is this correct?
}

/*
 * Method: get_forward_item
 *
 * Returns: the WebHistoryItem that succeeds the current item
 * in the WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_forward_item(self)
    VALUE self;
{
    WebKitWebHistoryItem* item;
    item = webkit_web_back_forward_list_get_forward_item(_BFLIST_SELF(self));
    return GOBJ2RVAL(item); // FIXME: is this correct?
}

/*
 * Method: get_nth_item
 *
 * Returns: the nth WebHistoryItem in the WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_nth_item(self, rb_num)
    VALUE self, rb_num;
{
    WebKitWebHistoryItem* item;
    item = webkit_web_back_forward_list_get_nth_item(
        _BFLIST_SELF(self),
        NUM2INT(rb_num)
        );
    return GOBJ2RVAL(item); // FIXME: is this correct?
}

/*
 * Method: get_back_length
 *
 * Returns: the number of items behind the current in the
 * WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_back_length(self)
    VALUE self;
{
    gint length;
    length = webkit_web_back_forward_list_get_back_length(_BFLIST_SELF(self));
    return INT2FIX(length);
}

/*
 * Method: get_forward_length
 *
 * Returns: the number of items ahead of the current item in the
 * WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_forward_length(self)
    VALUE self;
{
    gint length;
    length = webkit_web_back_forward_list_get_forward_length(_BFLIST_SELF(self));
    return INT2FIX(length);
}

/*
 * Method: get_limit
 *
 * Returns: the maximum number of items in the WebBackForwardList.
 *
 */
static VALUE
wk_bflist_get_limit(self)
    VALUE self;
{
    gint limit;
    limit = webkit_web_back_forward_list_get_limit(_BFLIST_SELF(self));
    return INT2FIX(limit);
}

/*
 * Method: set_limit
 *
 * Sets the maximum number of items in the WebBackForwardList. 
 *
 * Returns: self.
 *
 */
static VALUE
wk_bflist_set_limit(self, rb_limit)
    VALUE self;
{
    webkit_web_back_forward_list_set_limit(_BFLIST_SELF(self), NUM2INT(rb_limit));
    return self;
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
    rb_define_method(rb_cWebHistoryItem, "get_alternate_title", wk_histitem_get_alternate_title, 0);
    rb_define_method(rb_cWebHistoryItem, "set_alternate_title", wk_histitem_set_alternate_title, 1);
    rb_define_method(rb_cWebHistoryItem, "get_uri", wk_histitem_get_uri, 0);
    rb_define_method(rb_cWebHistoryItem, "get_original_uri", wk_histitem_get_original_uri, 0);
    rb_define_method(rb_cWebHistoryItem, "get_last_visited_time_in_seconds", wk_histitem_get_last_visited_time_in_seconds, 0);

//    G_DEF_SETTERS(rb_cWebHistoryItem);

    VALUE rb_cWebBackForwardList = G_DEF_CLASS(WEBKIT_TYPE_WEB_BACK_FORWARD_LIST, "WebBackForwardList", rb_mWebKit);
    rb_define_method(rb_cWebBackForwardList, "initialize", wk_bflist_initialize, 1);
    rb_define_method(rb_cWebBackForwardList, "go_back", wk_bflist_go_back, 0);
    rb_define_method(rb_cWebBackForwardList, "go_forward", wk_bflist_go_forward, 0);
    rb_define_method(rb_cWebBackForwardList, "contains_item?", wk_bflist_contains_item, 1);
    rb_define_method(rb_cWebBackForwardList, "go_to_item", wk_bflist_go_to_item, 1);
    rb_define_method(rb_cWebBackForwardList, "get_forward_list_with_limit", wk_bflist_get_forward_list_with_limit, 1);
    rb_define_method(rb_cWebBackForwardList, "get_back_list_with_limit", wk_bflist_get_back_list_with_limit, 1);
    rb_define_method(rb_cWebBackForwardList, "get_nth_item", wk_bflist_get_nth_item, 1);
    rb_define_method(rb_cWebBackForwardList, "get_back_item", wk_bflist_get_back_item, 0);
    rb_define_method(rb_cWebBackForwardList, "get_current_item", wk_bflist_get_current_item, 0);
    rb_define_method(rb_cWebBackForwardList, "get_forward_item", wk_bflist_get_forward_item, 0);
    rb_define_method(rb_cWebBackForwardList, "get_back_length", wk_bflist_get_back_length, 0);
    rb_define_method(rb_cWebBackForwardList, "get_forward_length", wk_bflist_get_forward_length, 0);
    rb_define_method(rb_cWebBackForwardList, "get_limit", wk_bflist_get_limit, 0);
    rb_define_method(rb_cWebBackForwardList, "set_limit", wk_bflist_set_limit, 1);
}
