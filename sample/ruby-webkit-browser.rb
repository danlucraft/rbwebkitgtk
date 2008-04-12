
require 'src/lib/webkit'

win = Gtk::Window.new
win.signal_connect("destroy") { Gtk.main_quit }

wv = Gtk::WebKit::WebView.new

vbox = Gtk::VBox.new
hbox = Gtk::HBox.new

bar = Gtk::Toolbar.new

back = bar.append(Gtk::Stock::GO_BACK) {  
  wv.go_back
}

forward = bar.append(Gtk::Stock::GO_FORWARD) {  
  wv.go_forward
}

stop = bar.append(Gtk::Stock::STOP) {  
  wv.stop_loading
}

refresh = bar.append(Gtk::Stock::REFRESH) {  
  wv.reload
}

home = bar.append(Gtk::Stock::HOME) { 
  wv.open("http://www.google.com/")
#  wv.execute_script("alert('foo');")
}

hbox.pack_start(bar, false)
entry = Gtk::Entry.new

entry.signal_connect('activate') {
  wv.open(entry.text)
}

hbox.pack_start(entry, true)
vbox.pack_start(hbox, false)

status = Gtk::Statusbar.new
status.has_resize_grip=false
status_context = status.get_context_id("Link")

wv.signal_connect("hovering-over-link") do |_, _, link|
  status.pop(status_context)
  if link
    status.push(status_context, link)
  end
end

vbox.pack_start(wv)
vbox.pack_start(status, false)

win.add(vbox)
win.set_size_request(800, 600)
wv.load_html_string(<<-HTML)
<h1>Ruby-WebKitGtk Bindings</h1>
GPL 2.1
HTML
win.show_all

Gtk.main
