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
#include "webkit/webkitwebview.h"

#include "rbwebkitgtkversion.h"

#define _WEBVIEW_SELF(s) (WEBKIT_WEB_VIEW(RVAL2GOBJ(s)))
/* #define _HISTITEM_SELF(s) (WEBKIT_WEB_HISTORY_ITEM(RVAL2GOBJ(s))) */
/* #define _BFLIST_SELF(s) (WEBKIT_WEB_BACK_FORWARD_LIST(RVAL2GOBJ(s))) */

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
 * Method: set_maintains_back_forward_list(maintain)
 *
 * maintain: whether the WebView should maintain a WebBackForwardList (True or False)
 *
 * Returns: self.
 *
 */

/* static VALUE */
/* wk_webview_set_maintains_back_forward_list(self, maintain) */
/*     VALUE self, maintain; */
/* { */
/*     webkit_web_view_set_maintains_back_forward_list (_WEBVIEW_SELF(self), RVAL2CBOOL(maintain)); */
/*     return self; */
/* } */

/*
 * Method: get_back_forward_list
 *
 * Returns: the WebBackForwardList for this WebView.
 *
 */

/* static VALUE */
/* wk_webview_get_back_forward_list(self) */
/*     VALUE self; */
/* { */
/*     WebKitWebBackForwardList* bflist; */
/*     bflist = webkit_web_view_get_back_forward_list (_WEBVIEW_SELF(self)); */
/*     return GOBJ2RVAL(bflist); */
/* } */

/*
 * Method: go_to_history_item(item)
 *
 * item: the WebHistoryItem to load (WebHistoryItem).
 *
 * This method makes the WebView visit the history item.
 *
 * Returns: self.
 *
 */

/* static VALUE */
/* wk_webview_go_to_history_item(self, item) */
/*     VALUE self, item; */
/* { */
/*     webkit_web_view_go_to_back_forward_item (_WEBVIEW_SELF(self), _HISTITEM_SELF(item)); */
/*     return self; */
/* } */

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
 * Method: can_go_back_or_forward?(steps)
 *
 * steps: a number of steps
 *
 * This method reflects the status of the browsing history. Negative values
 * represent steps backward while positive values represent steps forward.
 *
 * Returns: True if the browser can go back or forwards by the given 
 * number of steps, False otherwise.
 *
 */
static VALUE
wk_webview_can_go_back_or_forward(self, steps)
    VALUE self, steps;
{
    return CBOOL2RVAL(webkit_web_view_can_go_back_or_forward(
                          _WEBVIEW_SELF(self),
                          NUM2INT(steps)
                          ));
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
 * Method: search_text(text, case_sensitive, forward, wrap)
 *
 * text: the String to search for.
 * case_sensitive: True/False, case_sensitive?
 * forward: True/False, whether to search forwards.
 * wrap: True/False, continue looking at the beginning after reaching the end.
 *
 * Returns: True/False
 *
 */

static VALUE
wk_webview_search_text(self, text, case_sensitive, forward, wrap)
    VALUE self, text, forward, case_sensitive, wrap;
{
    gboolean found;
    found = webkit_web_view_search_text(
        _WEBVIEW_SELF(self), 
        RVAL2CSTR(text),
        RVAL2CBOOL(case_sensitive),
        RVAL2CBOOL(forward),
        RVAL2CBOOL(wrap)
        );
    return CBOOL2RVAL(found);
}

/*
 * Method: mark_text_matches_with_limit(text, case_sensitive, limit)
 *
 * text: the String to search for.
 * case_sensitive: True/False, case_sensitive?
 * limit: the maximum number of strings to look for (if 0, looks for all occurrences)
 *
 * Attempts to highlight all occurances of text inside WebView. These are 
 * not highlighted by default until unmark_text_matches is called.
 *
 * Returns: the number of strings highlighted.
 */

static VALUE
wk_webview_mark_text_matches_with_limit(self, text, case_sensitive, limit)
    VALUE self, text, case_sensitive, limit;
{
    gint num_found;
    num_found = webkit_web_view_mark_text_matches(
        _WEBVIEW_SELF(self), 
        RVAL2CSTR(text),
        RVAL2CBOOL(case_sensitive),
        NUM2INT(limit)
        );
    return INT2NUM(num_found);
}

/*
 * Method: set_highlight_text_matches(should_highlight)
 *
 * should_highlight: (True/False) whether to highlight matches
 *
 * Highlights text matches previously marked by mark_text_matches. 
 *
 * Returns: self.
 */

static VALUE
wk_webview_set_highlight_text_matches(self, should_highlight)
    VALUE self, should_highlight;
{
    webkit_web_view_set_highlight_text_matches(_WEBVIEW_SELF(self), RVAL2CBOOL(should_highlight));
    return self;
}

/*
 * Method: unmark_text_matches
 *
 * Removes highlighting previously set by mark_text_matches.
 *
 * Returns: self.
 */

static VALUE
wk_webview_unmark_text_matches(self)
    VALUE self;
{
    webkit_web_view_unmark_text_matches(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: can_cut_clipboard?
 *
 * Determines whether or not it is currently possible to cut to the clipboard.
 *
 * Returns: true or false.
 */

static VALUE
wk_webview_can_cut_clipboard(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_can_cut_clipboard(_WEBVIEW_SELF(self)));

}

/*
 * Method: can_copy_clipboard?
 *
 * Determines whether or not it is currently possible to copy to the clipboard.
 *
 * Returns: true or false.
 */

static VALUE
wk_webview_can_copy_clipboard(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_can_copy_clipboard(_WEBVIEW_SELF(self)));
}

/*
 * Method: can_paste_clipboard?
 *
 * Determines whether or not it is currently possible to paste from the clipboard.
 *
 * Returns: true or false.
 */

static VALUE
wk_webview_can_paste_clipboard(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_can_paste_clipboard(_WEBVIEW_SELF(self)));
}


/*
 * Method: cut_clipboard
 *
 * Cuts the current selection inside the WebView to the clipboard.
 *
 * Returns: self
 */

static VALUE
wk_webview_cut_clipboard(self)
    VALUE self;
{
    webkit_web_view_cut_clipboard(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: copy_clipboard
 *
 * Copies the current selection inside the WebView to the clipboard.
 *
 * Returns: self.
 */

static VALUE
wk_webview_copy_clipboard(self)
    VALUE self;
{
    webkit_web_view_copy_clipboard(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: paste_clipboard
 *
 * Pastes the current contents of the clipboard to the WebView.
 *
 * Returns: self.
 */

static VALUE
wk_webview_paste_clipboard(self)
    VALUE self;
{
    webkit_web_view_paste_clipboard(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: delete_selection
 *
 * Deletes the current selection inside the WebView.
 *
 * Returns: self.
 */

static VALUE
wk_webview_delete_selection(self)
    VALUE self;
{
    webkit_web_view_delete_selection(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: has_selection?
 *
 * Determines whether or not it text is currently selected.
 *
 * Returns: true or false.
 */

static VALUE
wk_webview_has_selection(self)
    VALUE self;
{
    return CBOOL2RVAL(webkit_web_view_has_selection(_WEBVIEW_SELF(self)));
}

/*
 * Method: get_selected_text
 *
 * Returns: the selected text, or nil if none.
 */

/* static VALUE */
/* wk_webview_get_selected_text(self) */
/*     VALUE self; */
/* { */
/*     gchar* text = webkit_web_view_get_selected_text(_WEBVIEW_SELF(self)); */
/*     return CSTR2RVAL(text); */
/* } */

/*
 * Method: select_all
 *
 * Attempts to select everything inside the @web_view.
 *
 * Returns: self.
 */

static VALUE
wk_webview_select_all(self)
    VALUE self;
{
    webkit_web_view_select_all(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: get_editable
 *
 * Returns: (True/False) whether the WebView is editable or not.
 *
 */
static VALUE
wk_webview_get_editable(self)
    VALUE self;
{
    gboolean editable;
    editable = webkit_web_view_get_editable(_WEBVIEW_SELF(self));
    return CBOOL2RVAL(editable);
}

/*
 * Method: set_editable(editable)
 *
 * editable: True/False, whether the WebView should be editable or not.
 *
 * By default a WebView is not editable.
 *
 * Returns: self.
 *
 */
static VALUE
wk_webview_set_editable(self, editable)
    VALUE self;
{
    webkit_web_view_set_editable(_WEBVIEW_SELF(self), RVAL2CBOOL(editable));
    return self;
}

/*
 * Method: get_uri
 *
 * Returns: uri
 * 
 */
static VALUE
wk_webview_get_uri(self)
    VALUE self;
{
    gchar* uri;
    uri = webkit_web_view_get_uri(_WEBVIEW_SELF(self));
    return CSTR2RVAL(uri);
}

/*
 * Method: zoom_in
 * 
 */
static VALUE
wk_webview_zoom_in(self)
    VALUE self;
{
    webkit_web_view_zoom_in(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: zoom_in
 * 
 */
static VALUE
wk_webview_zoom_out(self)
    VALUE self;
{
    webkit_web_view_zoom_out(_WEBVIEW_SELF(self));
    return self;
}

/*
 * Method: get_copy_target_list
 *
 * This function returns the list of targets this WebView can
 * provide for clipboard copying and as DND source. The targets in the list are
 * added with info values from the #WebKitWebViewTargetInfo enum,
 * using gtk_target_list_add() and gtk_target_list_add_text_targets().
 *
 * Returns: A Gtk::TargetList
 *
 */

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
/* static VALUE */
/* wk_histitem_initialize(self, rb_uri, rb_title) */
/*     VALUE self, rb_uri, rb_title; */
/* { */
/*     G_INITIALIZE(self, WEBKIT_WEB_HISTORY_ITEM ( */
/*                      webkit_web_history_item_new_with_data ( */
/*                          RVAL2CSTR(rb_uri),  */
/*                          RVAL2CSTR(rb_title) */
/*                          ))); */
/*     return Qnil; */
/* } */

/*
 * Method: get_title
 *
 * Returns: the page title of the WebHistoryItem.
 *
 */
/* static VALUE */
/* wk_histitem_get_title(self) */
/*     VALUE self; */
/* { */
/*     gchar* title; */
/*     title = (gchar *) webkit_web_history_item_get_title(_HISTITEM_SELF(self)); */
/*     return CSTR2RVAL(title); */
/* } */

/*
 * Method: get_alternate_title
 *
 * Returns: the alternate title of the WebHistoryItem.
 *
 */
/* static VALUE */
/* wk_histitem_get_alternate_title(self) */
/*     VALUE self; */
/* { */
/*     gchar* title; */
/*     title = (gchar *) webkit_web_history_item_get_alternate_title(_HISTITEM_SELF(self)); */
/*     return CSTR2RVAL(title); */
/* } */

/*
 * Method: set_alternate_title
 *
 * Sets an alternate title for the WebHistoryItem.
 *
 * Returns: self.
 *
 */
/* static VALUE */
/* wk_histitem_set_alternate_title(self, rb_title) */
/*     VALUE self, rb_title; */
/* { */
/*     webkit_web_history_item_set_alternate_title( */
/*         _HISTITEM_SELF(self), */
/*         RVAL2CSTR(rb_title) */
/*         ); */
/*     return self; */
/* } */

/*
 * Method: get_uri
 *
 * Returns: the page uri of the WebHistoryItem.
 *
 */
/* static VALUE */
/* wk_histitem_get_uri(self) */
/*     VALUE self; */
/* { */
/*     gchar* uri; */
/*     uri = (gchar *) webkit_web_history_item_get_uri(_HISTITEM_SELF(self)); */
/*     return CSTR2RVAL(uri); */
/* } */

/*
 * Method: get_original_uri
 *
 * Returns: the original uri of the WebHistoryItem.
 *
 */
/* static VALUE */
/* wk_histitem_get_original_uri(self) */
/*     VALUE self; */
/* { */
/*     gchar* uri; */
/*     uri = (gchar *) webkit_web_history_item_get_uri(_HISTITEM_SELF(self)); */
/*     return CSTR2RVAL(uri); */
/* } */

/*
 * Method: get_last_visited_time_in_seconds
 *
 * Returns: a time in seconds that the WebHistoryItem was last visited,
 *          or nil if this WebHistoryItem has never been visited.
 *
 */
/* static VALUE */
/* wk_histitem_get_last_visited_time_in_seconds(self) */
/*     VALUE self; */
/* { */
/*     gdouble time; */
/*     time = webkit_web_history_item_get_last_visited_time(_HISTITEM_SELF(self)); */
/*     if (time == 0) */
/*         return Qnil; */
/*     return LONG2NUM(time); */
/* } */

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
/* static VALUE */
/* wk_bflist_initialize(self, rb_webview) */
/*     VALUE self, rb_webview; */
/* { */
/*     G_INITIALIZE(self, WEBKIT_WEB_BACK_FORWARD_LIST ( */
/*                      webkit_web_back_forward_list_new_with_web_view ( */
/*                          _WEBVIEW_SELF(rb_webview) */
/*                          ))); */
/*     return Qnil; */
/* } */

/*
 * Method: go_forward
 *
 * FIXME
 *
 * Returns: self.
 *
 */
/* static VALUE */
/* wk_bflist_go_forward(self) */
/*     VALUE self; */
/* { */
/*     webkit_web_back_forward_list_go_forward(_BFLIST_SELF(self)); */
/*     return self; */
/* } */


/*
 * Method: go_back
 *
 * FIXME
 *
 * Returns: self.
 *
 */
/* static VALUE */
/* wk_bflist_go_back(self) */
/*     VALUE self; */
/* { */
/*     webkit_web_back_forward_list_go_back(_BFLIST_SELF(self)); */
/*     return self; */
/* } */

/*
 * Method: contains_item?
 *
 * Whether the WebBackForwardList contains the WebHistoryItem.
 *
 * Returns: true or false.
 *
 */
/* static VALUE */
/* wk_bflist_contains_item(self, rb_item) */
/*     VALUE self, rb_item; */
/* { */
/*     gboolean has; */
/*     has = webkit_web_back_forward_list_contains_item( */
/*         _BFLIST_SELF(self), */
/*         _HISTITEM_SELF(rb_item) */
/*         ); */
/*     return CBOOL2RVAL(has); */
/* } */

/*
 * Method: go_to_item
 *
 * FIXME
 *
 * Returns: self.
 *
 */
/* static VALUE */
/* wk_bflist_go_to_item(self, rb_item) */
/*     VALUE self, rb_item; */
/* { */
/*     webkit_web_back_forward_list_go_to_item( */
/*         _BFLIST_SELF(self), */
/*         _HISTITEM_SELF(rb_item) */
/*         ); */
/*     return self; */
/* } */

/*
 * Method: get_forward_list_with_limit
 *
 * Returns: an array of WebHistoryItems.
 *
 */
/* static VALUE */
/* wk_bflist_get_forward_list_with_limit(self, rb_limit) */
/*     VALUE self, rb_limit; */
/* { */
/*     GList* list; */
/*     list = webkit_web_back_forward_list_get_forward_list_with_limit( */
/*         _BFLIST_SELF(self), */
/*         NUM2INT(rb_limit) */
/*         ); */
/*     return GLIST2ARY(list); */
/* } */

/*
 * Method: get_back_list_with_limit
 *
 * Returns: an array of WebHistoryItems.
 *
 */

/* static VALUE */
/* wk_bflist_get_back_list_with_limit(self, rb_limit) */
/*     VALUE self, rb_limit; */
/* { */
/*     GList* list; */
/*     list = webkit_web_back_forward_list_get_back_list_with_limit( */
/*         _BFLIST_SELF(self), */
/*         NUM2INT(rb_limit) */
/*         ); */
/*     return GLIST2ARY(list); */
/* } */


/*
 * Method: get_back_item
 *
 * Returns: the WebHistoryItem that precedes the current item.
 *
 */
/* static VALUE */
/* wk_bflist_get_back_item(self) */
/*     VALUE self; */
/* { */
/*     WebKitWebHistoryItem* item; */
/*     item = webkit_web_back_forward_list_get_back_item(_BFLIST_SELF(self)); */
/*     return GOBJ2RVAL(item); // FIXME: is this correct? */
/* } */

/*
 * Method: get_current_item
 *
 * Returns: the currrent WebHistoryItem in the WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_current_item(self) */
/*     VALUE self; */
/* { */
/*     WebKitWebHistoryItem* item; */
/*     item = webkit_web_back_forward_list_get_current_item(_BFLIST_SELF(self)); */
/*     return GOBJ2RVAL(item); // FIXME: is this correct? */
/* } */

/*
 * Method: get_forward_item
 *
 * Returns: the WebHistoryItem that succeeds the current item
 * in the WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_forward_item(self) */
/*     VALUE self; */
/* { */
/*     WebKitWebHistoryItem* item; */
/*     item = webkit_web_back_forward_list_get_forward_item(_BFLIST_SELF(self)); */
/*     return GOBJ2RVAL(item); // FIXME: is this correct? */
/* } */

/*
 * Method: get_nth_item
 *
 * Returns: the nth WebHistoryItem in the WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_nth_item(self, rb_num) */
/*     VALUE self, rb_num; */
/* { */
/*     WebKitWebHistoryItem* item; */
/*     item = webkit_web_back_forward_list_get_nth_item( */
/*         _BFLIST_SELF(self), */
/*         NUM2INT(rb_num) */
/*         ); */
/*     return GOBJ2RVAL(item); // FIXME: is this correct? */
/* } */

/*
 * Method: get_back_length
 *
 * Returns: the number of items behind the current in the
 * WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_back_length(self) */
/*     VALUE self; */
/* { */
/*     gint length; */
/*     length = webkit_web_back_forward_list_get_back_length(_BFLIST_SELF(self)); */
/*     return INT2FIX(length); */
/* } */

/*
 * Method: get_forward_length
 *
 * Returns: the number of items ahead of the current item in the
 * WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_forward_length(self) */
/*     VALUE self; */
/* { */
/*     gint length; */
/*     length = webkit_web_back_forward_list_get_forward_length(_BFLIST_SELF(self)); */
/*     return INT2FIX(length); */
/* } */

/*
 * Method: get_limit
 *
 * Returns: the maximum number of items in the WebBackForwardList.
 *
 */
/* static VALUE */
/* wk_bflist_get_limit(self) */
/*     VALUE self; */
/* { */
/*     gint limit; */
/*     limit = webkit_web_back_forward_list_get_limit(_BFLIST_SELF(self)); */
/*     return INT2FIX(limit); */
/* } */

/*
 * Method: set_limit
 *
 * Sets the maximum number of items in the WebBackForwardList. 
 *
 * Returns: self.
 *
 */
/* static VALUE */
/* wk_bflist_set_limit(self, rb_limit) */
/*     VALUE self; */
/* { */
/*     webkit_web_back_forward_list_set_limit(_BFLIST_SELF(self), NUM2INT(rb_limit)); */
/*     return self; */
/* } */


/*                                                           */
/*************************************************************/

/** INIT **/

void 
Init_rbwebkitgtk()
{
    VALUE rb_mWebKit = rb_eval_string("Gtk::WebKit");
    VALUE rb_cWebView = G_DEF_CLASS(WEBKIT_TYPE_WEB_VIEW, "WebView", rb_mWebKit);

    rb_define_method(rb_cWebView, "initialize", wk_webview_initialize, 0);
    /* rb_define_method(rb_cWebView, "set_maintains_back_forward_list", wk_webview_set_maintains_back_forward_list, 1); */
    /* rb_define_method(rb_cWebView, "get_back_forward_list", wk_webview_get_back_forward_list, 0); */
    /* This is webkit_web_view_go_to_back_forward_item in the API: */
    /* rb_define_method(rb_cWebView, "go_to_history_item", wk_webview_go_to_history_item, 1); */
    rb_define_method(rb_cWebView, "can_go_back?", wk_webview_can_go_back, 0);
    rb_define_method(rb_cWebView, "can_go_back_or_forward?", wk_webview_can_go_back_or_forward, 1);
    rb_define_method(rb_cWebView, "can_go_forward?", wk_webview_can_go_forward, 0);
    rb_define_method(rb_cWebView, "go_back", wk_webview_go_back, 0);
    rb_define_method(rb_cWebView, "go_forward", wk_webview_go_forward, 0);
    rb_define_method(rb_cWebView, "stop_loading", wk_webview_stop_loading, 0);
    rb_define_method(rb_cWebView, "open", wk_webview_open, 1);
    rb_define_method(rb_cWebView, "reload", wk_webview_reload, 0);
    rb_define_method(rb_cWebView, "load_html_string", wk_webview_load_html_string, 2);
    rb_define_method(rb_cWebView, "execute_script", wk_webview_execute_script, 1);
    rb_define_method(rb_cWebView, "search_text", wk_webview_search_text, 4);
    rb_define_method(rb_cWebView, "mark_text_matches_with_limit", wk_webview_mark_text_matches_with_limit, 3);
    rb_define_method(rb_cWebView, "set_highlight_text_matches", wk_webview_set_highlight_text_matches, 1);
    rb_define_method(rb_cWebView, "unmark_text_matches", wk_webview_unmark_text_matches, 1);
    rb_define_method(rb_cWebView, "can_cut_clipboard?", wk_webview_can_cut_clipboard, 0);
    rb_define_method(rb_cWebView, "can_copy_clipboard?", wk_webview_can_copy_clipboard, 0);
    rb_define_method(rb_cWebView, "can_paste_clipboard?", wk_webview_can_paste_clipboard, 0);
    rb_define_method(rb_cWebView, "cut_clipboard", wk_webview_cut_clipboard, 0);
    rb_define_method(rb_cWebView, "copy_clipboard", wk_webview_copy_clipboard, 0);
    rb_define_method(rb_cWebView, "paste_clipboard", wk_webview_paste_clipboard, 0);
    rb_define_method(rb_cWebView, "delete_selection", wk_webview_delete_selection, 0);
    rb_define_method(rb_cWebView, "has_selection?", wk_webview_has_selection, 0);
/*     rb_define_method(rb_cWebView, "get_selected_text", wk_webview_get_selected_text, 0); */
    rb_define_method(rb_cWebView, "select_all", wk_webview_select_all, 0);
    rb_define_method(rb_cWebView, "get_editable", wk_webview_get_editable, 0);
    rb_define_method(rb_cWebView, "set_editable", wk_webview_set_editable, 1);
    rb_define_method(rb_cWebView, "get_uri", wk_webview_get_uri, 0);
    rb_define_method(rb_cWebView, "zoom_in", wk_webview_zoom_in, 0);
    rb_define_method(rb_cWebView, "zoom_out", wk_webview_zoom_out, 0);
/*     rb_define_method(rb_cWebView, "get_copy_target_list", wk_webview_get_copy_target_list, 0); */
/*     rb_define_method(rb_cWebView, "get_paste_target_list", wk_webview_get_paste_target_list, 0); */
/*     rb_define_method(rb_cWebView, "get_transparent", wk_webview_get_transparent, 0); */
/*     rb_define_method(rb_cWebView, "set_transparent", wk_webview_set_transparent, 1); */

    G_DEF_SETTERS(rb_cWebView);

/*     VALUE rb_cWebHistoryItem = G_DEF_CLASS(WEBKIT_TYPE_WEB_HISTORY_ITEM, "WebHistoryItem", rb_mWebKit); */
/*     rb_define_method(rb_cWebHistoryItem, "initialize", wk_histitem_initialize, 2); */
/*     rb_define_method(rb_cWebHistoryItem, "get_title", wk_histitem_get_title, 0); */
/*     rb_define_method(rb_cWebHistoryItem, "get_alternate_title", wk_histitem_get_alternate_title, 0); */
/*     rb_define_method(rb_cWebHistoryItem, "set_alternate_title", wk_histitem_set_alternate_title, 1); */
/*     rb_define_method(rb_cWebHistoryItem, "get_uri", wk_histitem_get_uri, 0); */
/*     rb_define_method(rb_cWebHistoryItem, "get_original_uri", wk_histitem_get_original_uri, 0); */
/*     rb_define_method(rb_cWebHistoryItem, "get_last_visited_time_in_seconds", wk_histitem_get_last_visited_time_in_seconds, 0); */

/* //    G_DEF_SETTERS(rb_cWebHistoryItem); */

    /* VALUE rb_cWebBackForwardList = G_DEF_CLASS(WEBKIT_TYPE_WEB_BACK_FORWARD_LIST, "WebBackForwardList", rb_mWebKit); */
    /* rb_define_method(rb_cWebBackForwardList, "initialize", wk_bflist_initialize, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "go_back", wk_bflist_go_back, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "go_forward", wk_bflist_go_forward, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "contains_item?", wk_bflist_contains_item, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "go_to_item", wk_bflist_go_to_item, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "get_forward_list_with_limit", wk_bflist_get_forward_list_with_limit, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "get_back_list_with_limit", wk_bflist_get_back_list_with_limit, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "get_nth_item", wk_bflist_get_nth_item, 1); */
    /* rb_define_method(rb_cWebBackForwardList, "get_back_item", wk_bflist_get_back_item, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "get_current_item", wk_bflist_get_current_item, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "get_forward_item", wk_bflist_get_forward_item, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "get_back_length", wk_bflist_get_back_length, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "get_forward_length", wk_bflist_get_forward_length, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "get_limit", wk_bflist_get_limit, 0); */
    /* rb_define_method(rb_cWebBackForwardList, "set_limit", wk_bflist_set_limit, 1); */
}
