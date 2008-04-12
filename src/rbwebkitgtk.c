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

#define _SELF(s) (WEBKIT_WEB_VIEW(RVAL2GOBJ(s)))

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

static VALUE
wk_webview_open(self, rb_url)
    VALUE self, rb_url;
{
    webkit_web_view_open (_SELF(self), RVAL2CSTR(rb_url));
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

    G_DEF_SETTERS(rb_cWebView);
}
