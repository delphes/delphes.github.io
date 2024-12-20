local meta = {}
local title = nil
local stringify = pandoc.utils.stringify

function get_title(h)
  if h.level == 1 and not title then
    title = h.content
    return {}
  end
end

function change_meta(m)
  meta = m
  p = m.page:gsub("/?index$", "")
  if p ~= "" then
    p = p .. "/"
  end
  m.canonical = stringify(m.base_url) .. "/" .. p
  m.title = title or m.site_title
  return m
end

function expand(s)
  v = meta[s]
  if v then
    return stringify(v)
  end
end

function change_link_target(l)
  l.target = l.target:gsub("%$(.-)%$", expand)
  if l.target:sub(1, 1) == "/" then
    l.target = meta.base_path .. l.target
  end
  return l
end

function change_image_src(i)
  if i.src:sub(1, 1) == "/" then
    i.src = meta.base_path .. i.src
  end
  return i
end

return {
  {
    Header = get_title,
    Meta = change_meta
  },
  {
    Link = change_link_target,
    Image = change_image_src
  }
}
