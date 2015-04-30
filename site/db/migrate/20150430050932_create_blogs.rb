class CreateBlogs < ActiveRecord::Migration
  def change
    create_table :blogs do |t|
      t.string :title
      t.text :content
      t.string :date
      t.string :image_url

      t.timestamps
    end
  end
end
