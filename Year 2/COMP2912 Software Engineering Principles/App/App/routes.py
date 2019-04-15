from flask import render_template, url_for, flash, redirect, request
from App import app, db
from App.forms import LoginForm, UpdateProfileForm, NewPostForm
from App.models import User, Post, Profile
from flask_login import login_user, current_user, logout_user, login_required

#route for forum page
#only accessible if logged in
@app.route("/forum", methods=['GET','POST'])
@login_required
def forum():
	posts = Post.query.all()
	return render_template('forum.html', title='Forum', posts=posts)

#route for login page and default page
@app.route("/", methods=['GET','POST'])
@app.route("/login", methods=['GET','POST'])
def login():
	#check if current user is authenticated
	#if authenticated stop user from coming back to login page
	if current_user.is_authenticated:
		return redirect(url_for('forum'))
	form = LoginForm()
	#check validation on form
	if form.validate_on_submit():
		#check user exists in database then log them in
		user = User.query.filter_by(email=form.email.data).first()
		if(user and form.password.data == user.password):
			login_user(user, remember=form.remember.data)
			#check next page args
			#will redirect user to page they attempted to access
			next_page = request.args.get('next')
			return redirect(next_page) if next_page else redirect(url_for('forum'))
		#produce error message otherwise
		else:
			flash('Unsuccessful. Please check email and password')
			return redirect(url_for('login'))
	return render_template('login.html', title='Login',form=form)

#log out route
@app.route('/logout')
def logout():
	logout_user()
	return redirect(url_for('login'))

#profile route
#only accessible if logged in
@app.route('/profile', methods=['GET','POST'])
@login_required
def profile():
	form = UpdateProfileForm()
	profile = Profile.query.filter_by(email=current_user.id).first()
	if form.validate_on_submit():
		profile.tiredness = form.tiredness.data
		profile.stress = form.stress.data
		db.session.commit()
		flash('Successful Update')
		return redirect(url_for('profile'))
	elif request.method == 'GET':
		form.tiredness.data = profile.tiredness
		form.stress.data = profile.stress
	return render_template('profile.html', title='Profile', form=form, profile=profile)

@app.route('/post/new', methods=['GET','POST'])
@login_required
def new_post():
	form = NewPostForm()
	if form.validate_on_submit():
		post = Post(title=form.title.data, content=form.content.data, po_id=current_user)
		db.session.add(post)
		db.session.commit()
		flash('Successful Post')
		return redirect(url_for('forum'))
	return render_template('new_post.html', title='New Post', form=form)
