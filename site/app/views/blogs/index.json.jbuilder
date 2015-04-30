json.array!(@blogs) do |blog|
  json.extract! blog, :id, :title, :content, :date, :image_url
  json.url blog_url(blog, format: :json)
end
