require 'gtk2'
module Gtk
  module WebKit
  end
end

require 'rbwebkitgtk.so'

class Gtk::WebKit::WebView
  alias :load_html_string_no_defaults :load_html_string
  def load_html_string(content, base_uri=nil)
    load_html_string_no_defaults(content, base_uri)
  end
  
  def mark_text_matches(test, case_sensitive=false, limit=0)
    mark_text_matches_with_limit(test, case_sensitive, limit)
  end
end
