class Blog < ActiveRecord::Base
  validates :title, :content, :date, :image_url, presence: true
end
