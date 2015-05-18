class MainController < ApplicationController
  def index
    @blogs = Product.order(:date)    
  end
end
